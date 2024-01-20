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
        ProbableAction(double probability, int action) :
            probability(probability),
            action(action) {}

        double probability;
        int action;
    };

    /**
     * Represents the policy in a markov decision process.
     */
    class Policy
    {
    public:
        Policy(const vector<vector<ProbableAction>>& mappings);
        const vector<ProbableAction>& getActions(int state) const;
        const vector<vector<ProbableAction>>& getAllActions() const;

    private:
        vector<vector<ProbableAction>> _mappings;
    };
} // namespace mdp

#endif