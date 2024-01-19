#include <vector>
#include <memory>
#include <iostream>
#include "../mdp/action.h"
#include "../mdp/state.h"
#include "../mdp/transition.h"
#include "../mdp/problem.h"

mdp::Problem getCoinFlipProblem(double ChanceOfHeads)
{
    mdp::Problem p(100, 101, 0);
    vector<shared_ptr<mdp::Action>> actions;
    for (int i = 0; i < 99; i++)
    {
        auto action = make_shared<mdp::Action>("bet " + i + 1, i);
        actions.push_back(action);
        p.registerAction(action);
    }

    vector<shared_ptr<mdp::State>> states;
    states.push_back(make_shared<mdp::State>("have 0",
        0,
        vector<shared_ptr<mdp::Transition>>(0)));
    p.registerState(states[0]);

    for (int i = 1; i <= 99; i++)
    {
        vector<shared_ptr<mdp::Transition>> validTransitions;

        for (int j = 1; j <= i; j++)
        {
            validTransitions.push_back(
                make_shared<mdp::Transition>(j - 1,
                    i + j,
                    ChanceOfHeads,
                    i + j == 100 ? 1 : 0));
            validTransitions.push_back(
                make_shared<mdp::Transition>(j - 1, i - j, 1 - ChanceOfHeads, 0));
        }
        states.push_back(make_shared<mdp::State>("have " + i, i, validTransitions));
        p.registerState(states.back());
    }

    states.push_back(make_shared<mdp::State>("have 100",
        100,
        vector<shared_ptr<mdp::Transition>>(0)));
    p.validate();
    return p;
}

int main()
{
    mdp::Problem p = getCoinFlipProblem(0.4);
    cout << "Hello World" << endl;
}