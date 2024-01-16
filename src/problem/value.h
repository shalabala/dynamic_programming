#ifndef DP_POLICY_H
#define DP_POLICY_H
#include <unordered_map>
#include <memory>
#include "iproblem.h"
#include "policy.h"
#include "state.h"
namespace mdp
{
    /**
     * Value function of a markov decision process.
    */
    class ValueFunction
    {
        public:
            static ValueFunction createRandomizedValueFunction(std::shared_ptr<IProblem> problem);
            /**
             * Performs one step of value iteration on the value function.
             * Returns the biggest difference between the old and the current value.
            */
            double performIteration();
            /**
             * Gets the policy that is eager based on this value function.
            */
            Policy getPolicy();

        private:
            std::unordered_map<std::shared_ptr<const State>, double> _mappings;
            std::shared_ptr<IProblem> _decisionProblem;


    };

} // namespace mdp

#endif