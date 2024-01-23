#include "mdp.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "settings.h"

void setStateActions(State *state, int numOfActions, ...)
{
    va_list args;
    va_start(args, numOfActions);

    int *stateActions = malloc(sizeof(int) * numOfActions);
    for (int i = 0; i < numOfActions; ++i)
    {
        stateActions[i] = va_arg(args, int);
    }
    state->numOfPossibleActions = numOfActions;
    state->possibleActions = stateActions;
}

Action *createAction(int id, char *name)
{
    Action *action = malloc(sizeof(Action));
    action->id = id;
    int lenOfName = strlen(name);
    action->name = malloc(sizeof(char) * lenOfName + 1);
    strcpy(action->name, name);
    return action;
}

void addAction(MDP *mdp, int id, char *name)
{
    mdp->actions[id] = createAction(id, name);
}

MDP *getMDP()
{
    MDP *mdp = malloc(sizeof(MDP));
    mdp->numOfStates = 6;
    mdp->states = malloc(sizeof(State) * mdp->numOfStates);
    char stateNamePattern[] = "State # ";
    int stateNameLength = strlen(stateNamePattern) + 1;
    for (int i = 0; i < mdp->numOfStates; ++i)
    {
        stateNamePattern[stateNameLength - 2] = i + '0';
        State *state = malloc(sizeof(State));
        state->id = i;
        state->name = malloc(sizeof(char) * stateNameLength);
        strcpy(state->name, stateNamePattern);
        mdp->states[i] = state;
    }
    mdp->numOfActions = 7;
    mdp->actions = malloc(sizeof(Action) * mdp->numOfActions);
    addAction(mdp, 0, "right");
    addAction(mdp, 1, "left");
    addAction(mdp, 2, "up");
    addAction(mdp, 3, "down");
    addAction(mdp, 4, "right up");
    addAction(mdp, 5, "left down");
    addAction(mdp, 6, "right down");

    setStateActions(mdp->states[0], 2, 0, 3);
    setStateActions(mdp->states[1], 2, 2, 4);
    setStateActions(mdp->states[2], 3, 0, 1, 5);
    setStateActions(mdp->states[3], 3, 0, 1, 6);
    setStateActions(mdp->states[4], 0);
    setStateActions(mdp->states[5], 0);

    mdp->discounting = DISCOUNTING;

    reset(mdp);
    return mdp;
}

void reset(MDP *mdp)
{
    mdp->currentState = mdp->states[0];
    mdp->lastReward = 0;
    mdp->actionsTaken = 0;
}

void freeMDP(MDP *mdp)
{
    for (int i = 0; i < mdp->numOfActions; ++i)
    {
        Action *a = mdp->actions[i];
        free(a->name);
        free(a);
    }
    for (int i = 0; i < mdp->numOfStates; ++i)
    {
        State *s = mdp->states[i];
        free(s->name);
        free(s->possibleActions);
        free(s);
    }
    free(mdp);
}

void performAction(MDP *mdp, int action)
{
    ++mdp->actionsTaken;
    switch (mdp->currentState->id)
    {
    case 0: // state 0
        switch (action)
        {
        case 0: // right goes to state 2
            mdp->currentState = mdp->states[2];
            return;
        case 3: // down goes to state 1
            mdp->currentState = mdp->states[1];
            return;
        default:
            printf("Illegal action %d from state %d", action, mdp->currentState->id);
            exit(-1);
            return;
        }
    case 1:
        switch (action)
        {
        case 2: // up goes to state 0
            mdp->currentState = mdp->states[0];
            return;
        case 4: // right up goes to state 2
            mdp->currentState = mdp->states[2];
            return;
        default:
            printf("Illegal action %d from state %d", action, mdp->currentState->id);
            exit(-1);
            return;
        }
    case 2:
        switch (action)
        {
        case 0: // right goes to state 3
            mdp->currentState = mdp->states[3];
            return;
        case 1: // left goes to state 0
            mdp->currentState = mdp->states[0];
            return;
        case 5: // left down goes to state 1
            mdp->currentState = mdp->states[1];
            return;
        default:
            printf("Illegal action %d from state %d", action, mdp->currentState->id);
            exit(-1);
            return;
        }
    case 3:
        switch (action)
        {
        case 0: // right goes to state 2
            mdp->currentState = mdp->states[4];
            mdp->lastReward = POS_REWARD;
            return;
        case 6: // right goes to state 2
            mdp->currentState = mdp->states[5];
            mdp->lastReward = NEG_REWARD;
            return;
        case 1: // left goes to state 2
            mdp->currentState = mdp->states[2];
            return;
        default:
            printf("Illegal action %d from state %d", action, mdp->currentState->id);
            exit(-1);
            return;
        }
    case 4:
        printf("Illegal action %d from state %d", action, mdp->currentState->id);
        exit(-1);
        return;
    case 5:
        printf("Illegal action %d from state %d", action, mdp->currentState->id);
        exit(-1);
        return;

    default:
        printf("Illegal action %d from state %d", action, mdp->currentState->id);
        exit(-1);
    }
}
