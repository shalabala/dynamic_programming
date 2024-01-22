#include "action.h"

namespace mdp 
{
    Action::Action(const std::string &name, int id): _name(name), _id(id) {}

    int Action::getId() const
    {
        return _id;
    }
    
    const std::string &Action::getName() const
    {
        return _name;
    }
}