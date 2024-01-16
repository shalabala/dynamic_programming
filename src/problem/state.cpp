#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "action.h"

export module mdp;
using namespace std;

namespace mdp{
    export class State{
        
        public:
            State(const string& name, int id, const vector<shared_ptr<Transition>>& transitions): 
                                                                            _name(name),
                                                                            _id(id),
                                                                            _transitions(transitions)
                                                                            {}
            const vector<shared_ptr<Action>>& getPossibleActions() const
            {

            }
            const vector<shared_ptr<Transition>>& getPossibleTransitions(const Action& a) const
            {

            }
            int getId() const
            {

            }
            const string& getName() const
            {
            }

        private:
            const string _name;
            const int _id;
            vector<shared_ptr<Transition>> _transitions;
            CachedState _cachedState;

        
    };

    class CachedState
    {
        public:
            /**
             * Wether a possible actions list has been cached.
            */
            bool hasCacheForPossibleActions() const
            {
                return _possibleActions != nullptr;
            }

            /**
             * Gets the possible actions, if a cache is already present. Otherwise throws an logic_error exception.
            */
            const vector<shared_ptr<Action>>& getPossibleActions()
            {
                if(_possibleActions)
                {
                    return *_possibleActions;
                }else 
                {
                    throw logic_error("Attempted to dereference a null pointer: possibleActions has not yet been cached");
                }
            }

            /**
             * Saves the value in the cache as the possible actions;
            */
            void savePossibleActions(const vector<shared_ptr<Transition>>& transitions)
            {
                _possibleActions = make_unique<vector<shared_ptr<Action>>>();
                for(auto&& t: transitions)
                {
                    _possibleActions->push_back(t->getCausingAction());
                }
            }

            bool hasCacheForPossibleTransition(const Action& a);
            const vector<shared_ptr<Transition>>& getPossibleTransition(const Action& a);

        private:
            unique_ptr<vector<shared_ptr<Action>>> _possibleActions;
            unordered_map<int, shared_ptr<vector<shared_ptr<Transition>>>
                


    };
    struct Transition{
        public:
            Transition(double probability, double reward, const shared_ptr<const Action> causingAction, const shared_ptr<const State> state);
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
    class State
}