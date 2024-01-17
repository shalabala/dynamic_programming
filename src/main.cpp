#include <vector>
#include <memory>
#include "../mdp/action.h"
#include "../mdp/state.h"
#include "../mdp/transition.h"


int main()
{
    vector<shared_ptr<mdp::Action>> actions(100);
    for (int i = 1; i <= 100; i++)
    {
        actions.push_back(make_shared<mdp::Action>("bet " + i, i));

    }
    vector<shared_ptr<mdp::State>> states(101);
    states.push_back(make_shared<mdp::State>("have 0", 0, vector<mdp::Transition>()));
    for (int i = 1; i <= 100; i++)
    {
        actions.push_back(make_shared<mdp::State>("have "+i,
        i,
        {
            make_shared<mdp::Transition>()
            
        }));

    }


    return 0;
}