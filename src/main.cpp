#include <vector>
#include <memory>
#include "../mdp/action.h"
#include "../mdp/state.h"
#include "../mdp/transition.h"
#include "../mdp/problem.h"

int main()
{
    mdp::Problem p(2, 100, 101, 0);
    vector<shared_ptr<mdp::Action>> actions(100);
    for (int i = 1; i <= 100; i++)
    {
        actions.push_back(make_shared<mdp::Action>("bet " + i, i));
        p.registerAction(actions[i]);
    }

    vector<shared_ptr<mdp::State>> states(101);
    states.push_back(make_shared<mdp::State>("have 0",
        0,
        vector<shared_ptr<mdp::Transition>>(0)));
    p.registerState(states[0]);
    for (int i = 1; i <= 100; i++)
    {
        vector<shared_ptr<mdp::Transition>> validTransitions(i);
        for ()
            for ()
                states.push_back(make_shared(mdp::State("have " + i, i, )))

    }


    return 0;
}