#include "transition.h"
#include "action.h"
#include "state.h"

namespace mdp
{
    Transition::Transition(int causingAction,
        int state,
        double probability,
        double reward
    ) :
        _probability(probability),
        _reward(reward),
        _causingAction(causingAction),
        _state(state) {}

    double Transition::getProbability() const
    {
        return _probability;
    }

    double Transition::getReward() const
    {
        return _reward;
    }

    int Transition::getCausingActionId() const
    {
        return _causingAction;
    }

    int Transition::getStateId() const
    {
        return _state;
    }

}