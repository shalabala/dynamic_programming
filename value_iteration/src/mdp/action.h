#ifndef DP_ACTION_H
#define DP_ACTION_H
#include <string>

namespace mdp
{
    /**
     * Represents an action in a markov decision process. This class is implemented as immutable. Has
     * a name and an id. In a single process, no two actions should exist with the same Id.
    */
    class Action
    {
        public:
            /**
             * Creates the action object with the given id and id.
            */
            Action(const std::string& name, int id);

            /**
             * Gets the id.
            */
            int getId() const;

            /**
             * Gets the name.
            */
            const std::string& getName() const;
            
        private:
            const std::string _name;
            const int _id;
    };
}
#endif