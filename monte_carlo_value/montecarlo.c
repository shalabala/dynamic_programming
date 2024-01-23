#include "montecarlo.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define LIST_SIZE 16;

typedef struct
{
    int nextState;
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

void initRandomPolicy()
{
    srand(time(NULL));
}

int randomPolicy(MDP *mdp)
{
    State *s = mdp->currentState;
    int r = rand();
    int actionPosition = r % s->numOfPossibleActions;
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
    double g;

    for (int l = 0; l < numOfStates; ++l)
    {
        entries[l].average = 0;
        entries[l].numberOfUpdates = 0;
    }

    lastActionResult.shouldSample = 0;
    for (int i = 0; i < numberOfIterations; ++i)
    {
        clear(list);
        reset(mdp);
        lastActionResult.nextState = mdp->currentState->id;
        lastActionResult.actionTaken = -1;
        lastActionResult.rewardReceived = mdp->lastReward;
        append(list, &lastActionResult);
        while (mdp->currentState->numOfPossibleActions != 0)
        {
            lastActionResult.actionTaken = policy(mdp);
            performAction(mdp, lastActionResult.actionTaken);
            lastActionResult.nextState = mdp->currentState->id;
            lastActionResult.rewardReceived = mdp->lastReward;
            append(list, &lastActionResult);
        }
        
        g = 0;
        // marking the updates that need to be taken into account
        for (int j = 0; j < mdp->numOfStates; ++j)
        {
            flags[j] = 1;
        }
        for (size_t j = 0; j < list->size; ++j)
        {
            result = list->elements + j;

            if (flags[result->nextState])
            {
                flags[result->nextState] = 0;
                result->shouldSample = 1;
            }
        }
        // updating the averages
        for (int k = list->size - 1; k >= 0; --k)
        {
            result = list->elements + k;
            entry = entries + result->nextState;
            g = g * mdp->discounting + result->rewardReceived;
            // calculating running average
            if (result->shouldSample)
            {
                ++entry->numberOfUpdates;
                entry->average += (g - entry->average) / entry->numberOfUpdates;
            }
        }
    }

    free(list->elements);
    free(list);
    return entries;
}
