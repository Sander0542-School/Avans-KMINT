#ifndef KMINT_ASSESSMENT_WATERNODEACTOR_HPP
#define KMINT_ASSESSMENT_WATERNODEACTOR_HPP

#include "CollidableNodeActor.hpp"

namespace actors
{
    class WaterNodeActor : public CollidableNodeActor
    {
        public:
            explicit WaterNodeActor(kmint::map::map_node& node) : CollidableNodeActor(node)
            {
                if (node.node_info().kind != 'W')
                {
                    throw std::exception("Node is not a water kind");
                }
            }
    };
}

#endif //KMINT_ASSESSMENT_WATERNODEACTOR_HPP
