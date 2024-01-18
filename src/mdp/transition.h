#ifndef DP_TRANSACTION_H
#define DP_TRANSACTION_H
#include <memory>
#include "action.h"
#include "state.h"

using namespace std;

namespace mdp
{
    class State;
    class Transition {
    public:
        Transition(int causingAction,
            int state,
            double probability,
            double reward
        );

        double getProbability() const;
        double getReward() const;
        int getCausingActionId() const;
        int getStateId() const;

    private:
        double _probability;
        double _reward;
        int _causingAction;
        int _state;
    };
}
#endif