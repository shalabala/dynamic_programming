#include <memory>
#include <limits>
#include <algorithm>
#include <vector>
#include "value.h"
#include "state.h"
#include "action.h"
#include "../constants.h"

namespace mdp{
    double ValueFunction::performIteration()
    {
        double maxDifference = 0;

        for (auto &&entry : _mappings)
        {
            auto state = entry.first;
            auto oldValue = entry.second;
            auto actions = state->getPossibleActions();
            //terminal state has a static value of 0
            double maxActionValue = actions.size() == 0 ? 0 : constants::DoubleMinValue;
            for(auto &&action : actions)
            {
                auto transitions = state->getPossibleTransitions(*action);
                double actionValue = 0;
                for(auto &&transition : transitions)
                {
                    auto probability = transition->getProbability();
                    auto nextState = transition->getState();
                    auto reward = transition->getReward();
                    double valueForCurrentAction = probability * 
                                    (reward + 
                                        _decisionProblem->getDiscountingRate() * _mappings.at(nextState));
                    actionValue += valueForCurrentAction;
                }
                maxActionValue = std::max(actionValue, maxActionValue);
            }
            entry.second=maxActionValue;
            double difference = std::abs(oldValue - maxActionValue);
            maxDifference = std::max(difference, maxDifference);
        }
        return maxDifference;
    }
}
