#ifndef DP_STATE_H
#define DP_STATE_H

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include "action.h"
#include "transition.h"

using namespace std;

namespace mdp {
    class Transition;
    class State {

    public:
        /**
         * Creates the state instance.
         * @param name The name of the state.
         * @param id The id of the state.
        */
        State(const string& name, int id, const vector<shared_ptr<Transition>>& transitions);

        /**
         * Gets all possible actions for this state.
        */
        const unordered_set<int>& getPossibleActions() const;

        /**
         * Gets all possible transitions for the given action.
        */
        const vector<shared_ptr<Transition>>& getPossibleTransitions(int actionId) const;

        /**
         * Gets the state id.
        */
        int getId() const;

        /**
         * Gets the state name.
        */
        const string& getName() const;

        /**
         * Validates the state, wether it's probabilities all sum to one.
        */
        void validate() const;
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
            const unordered_set<int>& getPossibleActions() const;

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
            const vector<shared_ptr<Transition>>& getPossibleTransition(int actionId) const;

            /**
             * Registers the transitions into the cache.
            */
            void savePossibleTransition(const vector<shared_ptr<Transition>>& transitions);

        private:
            unique_ptr<unordered_set<int>> _possibleActions;
            unordered_map<int, vector<shared_ptr<Transition>>> _possibleTransitions;
        };
        const string _name;
        const int _id;
        vector<shared_ptr<Transition>> _transitions;
        mutable CachedState _cachedState;
    };


}
#endif