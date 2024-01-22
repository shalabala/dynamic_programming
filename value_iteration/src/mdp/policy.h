#ifndef DP_POLICY_H
#define DP_POLICY_H

#include <memory>
#include <vector>
#include <memory>
#include <unordered_map>
#include "action.h"
#include "state.h"

using namespace std;

namespace mdp
{
    struct ProbableAction
    {
    public:
        /**
         * Creates a ProbableAction instance.
        */
        ProbableAction(double probability, int action) :
            probability(probability),
            action(action) {}

        /**
         * Probability that the action is taken.
        */
        double probability;

        /**
         * The action to be taken.
        */
        int action;
    };

    /**
     * Represents the policy in a markov decision process.
     */
    class Policy
    {
    public:
        /**
         * Creates the Policy instance.
        */
        Policy(const vector<vector<ProbableAction>>& mappings);

        /**
         * Gets the actions associated to the given state.
        */
        const vector<ProbableAction>& getActions(int state) const;

        /**
         * Gets all the actions. The state id is the index for the vector.
        */
        const vector<vector<ProbableAction>>& getAllActions() const;

    private:
        vector<vector<ProbableAction>> _mappings;
    };
} // namespace mdp

#endif