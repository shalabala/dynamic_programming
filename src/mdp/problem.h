#ifndef DP_IPROBLEM_H
#define DP_IPROBLEM_H
#include <vector>
#include <memory>
#include "state.h"
#include "action.h"

namespace mdp
{
    class Problem
    {
    public:
        Problem(const std::vector<double>& rewards,
            const std::vector<shared_ptr<Action>>& actions,
            const std::vector<shared_ptr<State>>& states,
            double discountRate);
        const std::vector<double>& getRewards() const;
        const std::vector<shared_ptr<Action>>& getActions() const;
        const std::vector<shared_ptr<State>>& getStates() const;
        double getDiscountingRate() const;
    private:
        std::vector<double> _rewards;
        std::vector<shared_ptr<Action>> _actions;
        std::vector<shared_ptr<State>> _states;
        double _discountRate;
    };
}

#endif