#include "value.h"

#include <unordered_map>
#include <random>
#include "constants.h"

using namespace std;

namespace mdp {

    ValueFunction ValueFunction::createRandomizedValueFunction(std::shared_ptr<Problem> problem)
    {
        auto& states = problem->getStates();
        vector<double> mappings(states.size());
        ValueFunction vf(mappings, problem);
        return vf;
    }

    ValueFunction::ValueFunction(const vector<double>& mappings, const shared_ptr<Problem>& decisionProblem) :
        _mappings(mappings),
        _decisionProblem(decisionProblem) {}

    double ValueFunction::performIteration()
    {
        double maxDifference = 0;

        for (size_t i = 0; i < _mappings.size(); i++)
        {
            auto stateId = i;
            auto state = _decisionProblem->getState(stateId);
            auto oldValue = _mappings[i];
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
            _mappings[i] = maxActionValue;
            double difference = std::abs(oldValue - maxActionValue);
            maxDifference = std::max(difference, maxDifference);
        }
        return maxDifference;
    }
}