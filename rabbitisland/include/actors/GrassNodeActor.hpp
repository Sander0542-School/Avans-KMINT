#ifndef KMINT_ASSESSMENT_GRASSNODEACTOR_HPP
#define KMINT_ASSESSMENT_GRASSNODEACTOR_HPP

#include "CollidableNodeActor.hpp"

namespace actors
{
    class GrassNodeActor : public CollidableNodeActor
    {
        public:
            explicit GrassNodeActor(const kmint::map::map_node& node) : CollidableNodeActor(node)
            {
                if (node.node_info().kind != 'G')
                {
                    throw std::exception("Node is not a grass kind");
                }
            }
    };
}

#endif //KMINT_ASSESSMENT_GRASSNODEACTOR_HPP
