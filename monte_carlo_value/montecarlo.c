#include "montecarlo.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define LIST_SIZE 16;

typedef struct
{
    int originalState;
    int actionTaken;
    double rewardReceived;
    int shouldSample;
} ActionResult;

typedef struct
{
    ActionResult *elements;
    size_t size;
    size_t maxSize;
} ActionResultList;

void append(ActionResultList *list, const ActionResult *newElement)
{
    if (list->size == list->maxSize)
    {
        ActionResult *oldList = list->elements;
        list->maxSize *= 2;
        ActionResult *newList = malloc(sizeof(ActionResult) * list->maxSize);
        memcpy(newList, oldList, sizeof(ActionResult) * list->size);
        free(oldList);
        list->elements = newList;
    }
    list->elements[list->size] = *newElement;
    ++list->size;
    return;
}

void clear(ActionResultList *list)
{
    list->size = 0;
}

ActionResultList *emptyList()
{
    ActionResultList *list = malloc(sizeof(ActionResultList));
    list->maxSize = LIST_SIZE;
    list->size = 0;
    list->elements = malloc(sizeof(ActionResult) * list->maxSize);
    return list;
}

void freeList(ActionResultList *list)
{
    free(list->elements);
    free(list);
}

int randomPolicy(MDP *mdp)
{
    srand(time(NULL));
    State *s = mdp->currentState;
    int actionPosition = rand() % s->numOfPossibleActions;
    int actionId = s->possibleActions[actionPosition];
    return actionId;
    return 0;
}

ValueEntry *estimateValue(MDP *mdp, int numberOfIterations, Policy policy)
{
    int numOfStates = mdp->numOfStates;
    ValueEntry *entries = malloc(sizeof(ValueEntry) * mdp->numOfStates);
    ActionResultList *list = emptyList();
    ActionResult lastActionResult;
    int flags[mdp->numOfStates];
    ActionResult *result;
    ValueEntry *entry;

    for (int l = 0; l < numOfStates; ++l)
    {
        entries[l].average = 0;
        entries[l].numberOfUpdates = 0;
    }

    double g;
    lastActionResult.shouldSample = 0;
    for (int i = 0; i < numberOfIterations; ++i)
    {
        clear(list);
        reset(mdp);
        while (mdp->currentState->numOfPossibleActions != 0)
        {
            lastActionResult.originalState = mdp->currentState->id;
            lastActionResult.actionTaken = policy(mdp);
            performAction(mdp, lastActionResult.actionTaken);
            lastActionResult.rewardReceived = mdp->lastReward;
            append(list, &lastActionResult);
        }
        g = 0;
        // marking the updates that need to be taken into account
        for (int j = 0; j < list->size; ++j)
        {
            for (int j = 0; j < mdp->numOfStates; ++j)
            {
                flags[j] = 1;
            }
            result = list->elements + j;

            if (flags[result->originalState])
            {
                flags[result->originalState] = 0;
                result->shouldSample = 1;
            }
        }
        // updating the averages
        for (int k = list->size - 1; k >= 0; --k)
        {
            result = list->elements + k;
            entry = entries + result->originalState;
            g = g * mdp->discounting + result->rewardReceived;
            // calculating running average
            if (result->shouldSample)
            {
                ++entry->numberOfUpdates;
                entry->average += (g - entry->average) / entry->numberOfUpdates;
            }
        }
    }
    free(list);
    return entries;
}
