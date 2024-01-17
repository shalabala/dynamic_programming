#ifndef DP_TRANSACTION_H
#define DP_TRANSACTION_H
#include <memory>
#include "action.h"
#include "state.h"

using namespace std;

namespace mdp
{
    class State;
    class Transition{
        public:
            Transition(double probability, 
                            double reward,
                            shared_ptr<Action> causingAction, 
                            shared_ptr<State> state);

            double getProbability() const;
            double getReward() const;
            shared_ptr<Action> getCausingAction() const;
            shared_ptr<State> getState() const;

        private:
            double _probability;
            double _reward;
            shared_ptr<Action> _causingAction;
            shared_ptr<State> _state;
    };
}
#endif