#ifndef DP_IPROBLEM_H
#define DP_IPROBLEM_H
#include <vector>
#include <memory>
#include "state.h"
#include "action.h"

namespace mdp
{

    /**
     * Represents an MDP decision problem
    */
    class Problem
    {
    public:
        /**
         * Creates a Problem instance.
        */
        Problem(int numOfRewards,
            int numOfActions,
            int numOfStates,
            double discountRate);

        /**
         * Registers the state to its id. Throws exception if
         * id already registered.
        */
        void registerState(shared_ptr<State> state);

        /**
         * Registers the action to the id. Throws exception if
         * id already registered.
        */
        void registerAction(shared_ptr<Action> action);

        /**
         * Gets the state registered to the id.
        */
        shared_ptr<State> getState(int stateId);

        /**
         * Gets the action registered to the id.
        */
        shared_ptr<Action> getAction(int actionId);

        /**
         * Gets a list of all the possible rewards of this problem.
        */
        const std::vector<double>& getRewards() const;

        /**
         * Gets all the registered actions of this problem.
        */
        const std::vector<shared_ptr<Action>>& getActions() const;

        /**
         * Gets all the registered states of this problem.
        */
        const std::vector<shared_ptr<State>>& getStates() const;

        /**
         * Gets the discounting rate of this problem.
         */
        double getDiscountingRate() const;

        /**
         * Validates the problem. It checks wether exactly the specified
         * number of states, actions and rewards have been registered. If
         * the problem is in an invalid state, an exception is thrown.
        */
        void validate();
    private:
        int _numOfRewards;
        int _numOfActions;
        int _numOfStates;
        std::vector<double> _rewards;
        std::vector<shared_ptr<Action>> _actions;
        std::vector<shared_ptr<State>> _states;
        double _discountRate;
    };
}

#endif