#ifndef KMINT_ASSESSMENT_HOLENODEACTOR_HPP
#define KMINT_ASSESSMENT_HOLENODEACTOR_HPP

#include "CollidableNodeActor.hpp"

namespace actors
{
    class HoleNodeActor : public CollidableNodeActor
    {
        public:
            explicit HoleNodeActor(const kmint::map::map_node& node) : CollidableNodeActor(node)
            {
                if (node.node_info().kind != 'H')
                {
                    throw std::exception("Node is not a hole kind");
                }
            }
    };
}

#endif //KMINT_ASSESSMENT_HOLENODEACTOR_HPP
