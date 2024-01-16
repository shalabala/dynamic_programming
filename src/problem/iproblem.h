#ifndef DP_I_PROBLEM_H
#define DP_I_PROBLEM_H
#include <vector>
#include "action.h"
#include "state.h"
namespace mdp
{
    class IProblem
    {
        public:
        virtual ~IProblem() = default;
        virtual const std::vector<double>& getRewards() const = 0;
        virtual const std::vector<Action>& getActions() const = 0;
        virtual const std::vector<State>& getStates() const = 0;
        virtual const double getDiscountingRate() const = 0; 

    }
    
};
#endif