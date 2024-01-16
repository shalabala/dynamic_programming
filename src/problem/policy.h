#ifndef DP_POLICY_HH
#define DP_POLICY_HH
#include<memory>
#include<vector>
#include<memory>
#include<unordered_map>
#include "action.h"
#include "state.h"
namespace mdp
{
    /**
     * Represents the policy in a markov decision process.
    */
    class Policy{
        public:
            std::vector<ProbableAction> getActions(const State& state) const;
        private:
            std::unordered_map<std::shared_ptr<const State>, std::vector<ProbableAction>> mappings;
    };

    struct ProbableAction{

        public:
        private:
            double _probability;
            std::shared_ptr<Action> _action;

    };
    
} // namespace mdp

#endif