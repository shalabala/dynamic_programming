#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "mdp.h"

typedef int(*Policy)(MDP*);

typedef struct{
    int numberOfUpdates;
    double average;
} ValueEntry;

int randomPolicy(MDP *mdp);

ValueEntry *estimateValue(MDP *mdp, int numberOfIterations, Policy policy);

#endif