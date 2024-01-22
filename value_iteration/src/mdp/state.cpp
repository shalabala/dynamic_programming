#include "state.h"

#include <vector>
#include <string>
#include "transition.h"
using namespace std;

namespace mdp
{
    State::State(const string& name, int id, const vector<shared_ptr<Transition>>& transitions) :
        _name(name),
        _id(id),
        _transitions(transitions)
    {}

    const unordered_set<int>& State::getPossibleActions() const
    {
        if (!_cachedState.hasCacheForPossibleActions())
        {
            _cachedState.savePossibleActions(_transitions);
        }

        return _cachedState.getPossibleActions();
    }

    const vector<shared_ptr<Transition>>& State::getPossibleTransitions(int actionId) const
    {
        if (!_cachedState.hasCacheForPossibleTransitions())
        {
            _cachedState.savePossibleTransition(_transitions);
        }

        return _cachedState.getPossibleTransition(actionId);
    }

    int State::getId() const
    {
        return _id;
    }

    const string& State::getName() const
    {
        return _name;
    }

    bool State::CachedState::hasCacheForPossibleActions() const
    {
        return _possibleActions != nullptr;
    }

    const unordered_set<int>& State::CachedState::getPossibleActions() const
    {
        if (_possibleActions)
        {
            return *_possibleActions;
        }
        else
        {
            throw logic_error("Attempted to dereference a null pointer: possibleActions has not yet been cached");
        }
    }

    void State::CachedState::savePossibleActions(const vector<shared_ptr<Transition>>& transitions)
    {
        _possibleActions = make_unique<unordered_set<int>>();
        for (auto&& t : transitions)
        {
            _possibleActions->insert(t->getCausingActionId());
        }
    }

    bool State::CachedState::hasCacheForPossibleTransitions() const
    {
        return _possibleTransitions.size() > 0;
    }

    const vector<shared_ptr<Transition>>& State::CachedState::getPossibleTransition(int actionId) const
    {
        auto& vec = _possibleTransitions.at(actionId);
        return vec;
    }

    void State::CachedState::savePossibleTransition(const vector<shared_ptr<Transition>>& transitions)
    {
        for (auto&& transition : transitions)
        {
            auto id = transition->getCausingActionId();
            if (_possibleTransitions.contains(id))
            {
                _possibleTransitions[id].push_back(transition);
            }
            else
            {
                _possibleTransitions[id] = { transition };
            }
        }
    }

    void State::validate() const
    {
        auto& actions = getPossibleActions();
        for (auto&& action : actions)
        {
            auto& transitions = getPossibleTransitions(action);
            double sumOfProbabilities = 0;

            for (auto&& transition : transitions)
            {
                sumOfProbabilities += transition->getProbability();
            }

            if (sumOfProbabilities != 1) {
                throw logic_error("The probabilities of state " + _name + " do not sum up to 1 for action " + to_string(action));
            }
        }
    }
}