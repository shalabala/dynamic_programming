#include "value.h"

#include <unordered_map>
#include <random>
#include "constants.h"

using namespace std;
namespace mdp {
    const double Threshold = 0.0000000000001;

    ValueFunction ValueFunction::createRandomizedValueFunction(std::shared_ptr<Problem> problem)
    {
        auto& states = problem->getStates();
        vector<double> mappings(states.size());
        ValueFunction vf(mappings, problem);
        return vf;
    }

    Policy ValueFunction::getPolicy()
    {
        vector<vector<ProbableAction>> actionMappings(_mappings.size());
        for (size_t i = 0; i < _mappings.size(); i++)
        {
            auto state = _decisionProblem->getState(i);

            auto& actionsForThisState = actionMappings[i];
            double maxValueForAction = constants::DoubleMinValue;

            auto& actions = state->getPossibleActions();
            for (auto&& action : actions)
            {
                auto& transitions = state->getPossibleTransitions(action);
                double actionVal = 0;
                for (auto&& transition : transitions)
                {
                    actionVal += transition->getProbability() * (transition->getReward() + _mappings[transition->getStateId()]);
                }
                if (abs(actionVal - maxValueForAction) < Threshold)
                {
                    actionsForThisState.push_back(ProbableAction(1, action));
                }
                else if (actionVal > maxValueForAction)
                {
                    actionsForThisState.clear();
                    actionsForThisState.push_back(ProbableAction(1, action));
                    maxValueForAction = actionVal;
                }
            }

            //normalize probabilities
            for (auto&& probableAction : actionsForThisState)
            {
                probableAction.probability = 1.0 / actionsForThisState.size();
            }
        }
        return Policy(actionMappings);
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