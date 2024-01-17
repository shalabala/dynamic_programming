#ifndef DP_STATE_H
#define DP_STATE_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "action.h"
#include "transition.h"

using namespace std;

namespace mdp{
    class Transition;
    class State{
        
        public:
            State(const string& name, int id, const vector<shared_ptr<Transition>>& transitions);
            const vector<shared_ptr<Action>>& getPossibleActions() const;
            const vector<shared_ptr<Transition>>& getPossibleTransitions(const Action& a) const;
            int getId() const;
            const string& getName() const;
        private:
            class CachedState
            {
                public:
                    /**
                     * Wether a possible actions list has been cached.
                    */
                    bool hasCacheForPossibleActions() const;

                    /**
                     * Gets the possible actions, if a cache is already present. Otherwise throws an logic_error exception.
                    */
                    const vector<shared_ptr<Action>>& getPossibleActions() const;

                    /**
                     * Saves the value in the cache as the possible actions;
                    */
                    void savePossibleActions(const vector<shared_ptr<Transition>>& transitions);

                    /**
                     * Wether the cache has an entry for the given action.
                    */
                    bool hasCacheForPossibleTransitions() const;

                    /**
                     * Gets the cache entry for the given action.
                    */
                    const vector<shared_ptr<Transition>>& getPossibleTransition(const Action& a) const;
                    
                    /**
                     * Registers the transitions into the cache.
                    */
                    void savePossibleTransition(const vector<shared_ptr<Transition>>& transitions);

                private:
                    unique_ptr<vector<shared_ptr<Action>>> _possibleActions;
                    unordered_map<int, vector<shared_ptr<Transition>>> _possibleTransitions;
            };
            const string _name;
            const int _id;
            vector<shared_ptr<Transition>> _transitions;
            mutable CachedState _cachedState;
    };

    
}
#endif