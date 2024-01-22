#include "policy.h"

namespace mdp
{
    Policy::Policy(const vector<vector<ProbableAction>>& mappings) : _mappings(mappings)
    {
    }

    const vector<ProbableAction>& Policy::getActions(int state) const
    {
        return _mappings[state];
    }
    const vector<vector<ProbableAction>>& Policy::getAllActions() const
    {
        return _mappings;
    }
}
