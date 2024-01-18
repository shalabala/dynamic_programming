#include <unordered_map>
#include <memory>
#include "problem.h"
#include "policy.h"

namespace mdp
{
    /**
     * Value function of a markov decision process.
    */
    class ValueFunction
    {
    public:
        static ValueFunction createRandomizedValueFunction(std::shared_ptr<Problem> problem);
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
        std::unordered_map<int, double> _mappings;
        std::shared_ptr<Problem> _decisionProblem;


    };

} // namespace mdp