#ifndef MDP_H
#define MDP_H

typedef struct
{
    int id;
    char *name;
} Action;

typedef struct
{
    int id;
    char *name;
    int *possibleActions;
    int numOfPossibleActions;
} State;

typedef struct
{
    State **states;
    int numOfStates;

    Action **actions;
    int numOfActions;

    State *currentState;
    double lastReward;

    int actionsTaken;
    double discounting;
} MDP;

MDP *getMDP();

void reset(MDP *mdp);

void freeMDP(MDP *mdp);

void performAction(MDP *mdp, int action);

#endif
