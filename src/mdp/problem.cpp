#include "problem.h"

using namespace std;

namespace mdp
{
    Problem::Problem(const vector<double>& rewards,
        const vector<shared_ptr<Action>>& actions,
        const vector<shared_ptr<State>>& states,
        double discountRate) : _rewards(rewards),
        _actions(actions),
        _states(states),
        _discountRate(discountRate)
    {
    }

    const std::vector<double>& Problem::getRewards() const
    {
        return _rewards;
    }

    const std::vector<shared_ptr<Action>>& Problem::getActions() const
    {
        return _actions;
    }

    const std::vector<shared_ptr<State>>& Problem::getStates() const
    {
        return _states;
    }

    double Problem::getDiscountingRate() const
    {
        return _discountRate;
    }
}
