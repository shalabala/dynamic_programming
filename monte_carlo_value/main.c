#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "mdp.h"
#include "montecarlo.h"
#define NUM_OF_ITERATIONS 1000
/**
 * A simple state based game with a random policy. The goal is to find the exit of the maze. The maze:
 *  0.--2.--3.--4.
 *  |  /     \
 *  | /       \
 *  1.         5.
 *  State 0. is the beginning state.
 *  State 4. is the terminal state with reward POS_REWARD.
 *  State 5. is the terminal state with reward NEG_REWARD.
 *  Discounting is DISCOUNTING (constants defined in settings.h)
 *  Actions are:
 *      right : 0, left : 1, up : 2, down : 3, right up : 4, left down : 5
 */

int main()
{
    initRandomPolicy();
    MDP *mdp = getMDP();
    ValueEntry* values = estimateValue(mdp, NUM_OF_ITERATIONS, randomPolicy);
    for (int i = 0; i < mdp->numOfStates; ++i)
    {
        ValueEntry *element =values+i;
        printf("For state %d average value is %f after %d samplings\n", i, element->average, element->numberOfUpdates);
    }
    free(values);
    freeMDP(mdp);
    return 0;
}