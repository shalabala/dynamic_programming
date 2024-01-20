#include "problem.h"
#include <string>

using namespace std;

namespace mdp
{
    Problem::Problem(size_t numOfActions,
        size_t numOfStates,
        double discountRate) :
        _numOfActions(numOfActions),
        _numOfStates(numOfStates),
        _actions(numOfActions),
        _states(numOfStates),
        _discountRate(discountRate)
    {
        //filling up actions and states with null.
    }

    void Problem::registerState(shared_ptr<State> state)
    {
        auto& currentValue = _states[state->getId()];
        if (currentValue != nullptr) {
            throw logic_error("State " + to_string(state->getId()) + " cannot be registered twice");
        }
        _states[state->getId()] = state;
    }

    void Problem::registerAction(shared_ptr<Action> action)
    {
        auto& currentValue = _actions[action->getId()];
        if (currentValue != nullptr) {
            throw logic_error("State " + to_string(action->getId()) + " cannot be registered twice");
        }
        _actions[action->getId()] = action;
    }

    shared_ptr<State> Problem::getState(int stateId)
    {
        auto& currentValue = _states[stateId];
        if (currentValue == nullptr) {
            throw logic_error("State " + to_string(stateId) + " has not been registered.");
        }
        return currentValue;
    }

    shared_ptr<Action> Problem::getAction(int actionId)
    {
        auto& currentValue = _actions[actionId];
        if (currentValue == nullptr) {
            throw logic_error("State " + to_string(actionId) + " has not been registered.");
        }
        return currentValue;
    }

    const std::vector<shared_ptr<Action>>& Problem::getActions() const
    {
        return _actions;
    }

    const std::vector<shared_ptr<State>>& Problem::getStates() const
    {
        return _states;
    }

    double Problem::getDiscountingRate() const
    {
        return _discountRate;
    }

    void Problem::validate()
    {
        if (_states.size() != _numOfStates)
        {
            throw logic_error("inconsistent state");
        }

        for (auto&& state : _states)
        {
            if (!state)
            {
                throw logic_error("inconsistent state");
            }
            state->validate();
        }

        for (auto&& action : _actions)
        {
            if (!action)
            {
                throw logic_error("inconsistent state");
            }
        }
    }
}
