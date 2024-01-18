#include "value.h"
#include "constants.h"

namespace mdp {

    double ValueFunction::performIteration()
    {
        double maxDifference = 0;

        for (auto&& entry : _mappings)
        {
            auto stateId = entry.first;
            auto state = _decisionProblem->getState(stateId);
            auto oldValue = entry.second;
            auto actions = state->getPossibleActions();
            //terminal state has a static value of 0
            double maxActionValue = actions.size() == 0 ? 0 : constants::DoubleMinValue;
            for (auto&& actionId : actions)
            {
                auto transitions = state->getPossibleTransitions(actionId);
                double actionValue = 0;
                for (auto&& transition : transitions)
                {
                    auto probability = transition->getProbability();
                    auto nextState = transition->getStateId();
                    auto reward = transition->getReward();
                    double valueForCurrentAction = probability *
                        (reward +
                            _decisionProblem->getDiscountingRate() * _mappings.at(nextState));
                    actionValue += valueForCurrentAction;
                }
                maxActionValue = std::max(actionValue, maxActionValue);
            }
            entry.second = maxActionValue;
            double difference = std::abs(oldValue - maxActionValue);
            maxDifference = std::max(difference, maxDifference);
        }
        return maxDifference;
    }
}