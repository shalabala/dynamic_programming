#ifndef DP_IPROBLEM_H
#define DP_IPROBLEM_H
#include <vector>
#include "state.h"
#include "action.h"

namespace mdp
{
    class IProblem
    {
        public:
        virtual ~IProblem() = default;
        virtual const std::vector<double>& getRewards() const = 0;
        virtual const std::vector<Action>& getActions() const = 0;
        virtual const std::vector<State>& getStates() const = 0;
        virtual double getDiscountingRate() const = 0; 

    };
}

#endif