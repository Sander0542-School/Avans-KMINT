#ifndef KMINT_ASSESSMENT_NODE_HPP
#define KMINT_ASSESSMENT_NODE_HPP

#include <stdexcept>

using graph_type = kmint::map::map_graph;
using node_type = graph_type::node_type;

namespace algorithms
{
    struct Node
    {
        const node_type* node;
        std::pair<size_t, double> weight;
        double heuristic = 0;
        bool visited = false;
        bool tagged = false;

        friend bool operator<(Node const& lhs, Node const& rhs)
        {
            return lhs.heuristic + lhs.weight.second > rhs.heuristic + rhs.weight.second;
        }

        bool operator==(const Node& rhs) const
        {
            return node->node_id() == rhs.node->node_id();
        }

        bool operator!=(const Node& rhs) const
        {
            return !(rhs == *this);
        }
    };
}

#endif //KMINT_ASSESSMENT_NODE_HPP
