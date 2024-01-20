#include <vector>
#include <memory>
#include <iostream>
#include "../mdp/action.h"
#include "../mdp/state.h"
#include "../mdp/transition.h"
#include "../mdp/problem.h"
#include "../mdp/value.h"

/**
 * Assembles the coin flip problem, where a gambler have to bet some amount of his money on a coin flip.
 * If the coin comes up as heads, he gets doubles his money. If its tails, he looses it. He gets a reward of 1
 * if his ballance gets to 100, otherwise always 0.
*/
shared_ptr<mdp::Problem> getCoinFlipProblem(double chanceOfHeads)
{
    auto p = make_shared<mdp::Problem>(99, 101, 1);
    vector<shared_ptr<mdp::Action>> actions;
    for (int i = 0; i < 99; i++)
    {
        auto action = make_shared<mdp::Action>("bet " + to_string(i + 1), i);
        actions.push_back(action);
        p->registerAction(action);
    }

    vector<shared_ptr<mdp::State>> states;
    states.push_back(make_shared<mdp::State>("have 0",
        0,
        vector<shared_ptr<mdp::Transition>>(0)));
    p->registerState(states[0]);

    for (int i = 1; i <= 99; i++)
    {
        vector<shared_ptr<mdp::Transition>> validTransitions;

        for (int j = 1; j <= i; j++)
        {
            int action = j - 1;
            // heads transition, winning
            //max state is 100
            int state = min(i + j, 100);
            //if we reach state 100, we win
            double reward = state == 100 ? 1 : 0;
            validTransitions.push_back(
                make_shared<mdp::Transition>(action,
                    state, chanceOfHeads, reward));
            //tails transition
            //min state is 0
            state = max(i - j, 0);
            //reward is always 0 if we loose
            reward = 0;
            validTransitions.push_back(
                make_shared<mdp::Transition>(action, state, 1 - chanceOfHeads, reward));
        }
        states.push_back(make_shared<mdp::State>("have " + to_string(i), i, validTransitions));
        p->registerState(states.back());
    }

    states.push_back(make_shared<mdp::State>("have 100",
        100,
        vector<shared_ptr<mdp::Transition>>(0)));
    p->registerState(states.back());
    p->validate();
    return p;
}

int main()
{
    auto p = getCoinFlipProblem(0.4);
    auto valueFunction = mdp::ValueFunction::createRandomizedValueFunction(p);
    double e = 0.001;
    double difference = 2 * e;
    while (difference > e) {
        difference = valueFunction.performIteration();
    }

}