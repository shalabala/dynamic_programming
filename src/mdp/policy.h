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
    private:
        double _probability;
        std::shared_ptr<Action> _action;
    };

    /**
     * Represents the policy in a markov decision process.
     */
    class Policy
    {
    public:
        vector<ProbableAction> getActions(const State &state) const;

    private:
        unordered_map<shared_ptr<const State>, vector<ProbableAction>> mappings;
    };
} // namespace mdp

#endif