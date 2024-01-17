#include <vector>
#include "transition.h"
#include "state.h"
using namespace std;

namespace mdp
{
    State::State(const string& name, int id, const vector<shared_ptr<Transition>>& transitions): 
                                                                            _name(name),
                                                                            _id(id),
                                                                            _transitions(transitions)
                                                                            {}
                                                                            
    const vector<shared_ptr<Transition>>& State::getPossibleTransitions(const Action& a) const
    {
        if(!_cachedState.hasCacheForPossibleTransitions())
        {
            _cachedState.savePossibleTransition(_transitions);
        }

        return _cachedState.getPossibleTransition(a);
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

    const vector<shared_ptr<Action>>& State::CachedState::getPossibleActions() const
    {
        if(_possibleActions)
        {
            return *_possibleActions;
        }else 
        {
            throw logic_error("Attempted to dereference a null pointer: possibleActions has not yet been cached");
        }
    }

    void State::CachedState::savePossibleActions(const vector<shared_ptr<Transition>>& transitions)
    {
        _possibleActions = make_unique<vector<shared_ptr<Action>>>();
        for(auto&& t: transitions)
        {
            _possibleActions->push_back(t->getCausingAction());
        }
    }
     
    bool State::CachedState::hasCacheForPossibleTransitions() const
    {
        return _possibleTransitions.size() > 0;
    }

    const vector<shared_ptr<Transition>>& State::CachedState::getPossibleTransition(const Action& a) const
    {
        auto& vec = _possibleTransitions.at(a.getId());
        return vec;
    }
            
    void State::CachedState::savePossibleTransition(const vector<shared_ptr<Transition>>& transitions)
    {
        for(auto&& transition: transitions)
        {
            auto id = _possibleTransitions.contains(transition->getCausingAction()->getId());
            if(_possibleTransitions.contains(id))
            {
                _possibleTransitions[id].push_back(transition);
            }
            else
            {
                _possibleTransitions[id]={transition};
            }
        }
    }
}