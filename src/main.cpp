#include "../mdp/iproblem.h"
#include "../mdp/action.h"
#include "../mdp/state.h"

class Problem : public mdp::IProblem{
    const std::vector<double>& getRewards() const override
    {

    }
    const std::vector<mdp::Action>& getActions() const override
    {

    }
    const std::vector<mdp::State>& getStates() const override
    {

    }
    double getDiscountingRate() const override
    {

    }

};

int main()
{
    return 0;
}