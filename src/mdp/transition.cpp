#include "transition.h"
#include "action.h"
#include "state.h"

namespace mdp
{
    Transition::Transition(shared_ptr<Action> causingAction,
        shared_ptr<State> state,
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
    shared_ptr<Action> Transition::getCausingAction() const
    {
        return _causingAction;
    }
    shared_ptr<State> Transition::getState() const
    {
        return _state;
    }

}