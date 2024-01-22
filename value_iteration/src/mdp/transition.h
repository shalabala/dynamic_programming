#ifndef DP_TRANSACTION_H
#define DP_TRANSACTION_H
#include <memory>
#include "action.h"
#include "state.h"

using namespace std;

namespace mdp
{
    class State;
    /**
     * A class representing a transition. The transition has a causing action, a state that this action transitions the MDP, a probability
     * with which this occurs, and a reward value. In an MDP, under one state, all transition probabilities with the same action
     * should sum up to one.
    */
    class Transition {
    public:
        /**
         * Creates the transition instance.
        */
        Transition(int causingAction,
            int state,
            double probability,
            double reward
        );

        /**
         * Gets the probability of the transition.
        */
        double getProbability() const;

        /**
         * Gets the reward of the transition.
        */
        double getReward() const;

        /**
         * Gets the causing action of the transition.
        */
        int getCausingActionId() const;

        /**
         * Gets the state id, to which this transition is going.
        */
        int getStateId() const;

    private:
        double _probability;
        double _reward;
        int _causingAction;
        int _state;
    };
}
#endif