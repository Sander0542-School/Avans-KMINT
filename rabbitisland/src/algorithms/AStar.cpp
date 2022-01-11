#include "algorithms/AStar.hpp"

#include <algorithm>
#include <queue>

using namespace algorithms;
using namespace kmint;

AStar::AStar(map::map_graph& graph, bool visualize) : PathAlgo(graph, visualize)
{
}

std::vector<node_type*> AStar::find(const node_type& begin, const node_type& end) const noexcept
{
    if (_visualize) _graph.untag_all();

    auto visited_nodes = find_visited(begin, end);
    if (_visualize)
    {
        for (const auto& node: visited_nodes)
        {
            if (node.second.visited)
                _graph[node.first].tag(kmint::graph::node_tag::visited);
        }
    }

    auto path_nodes = find_path(visited_nodes, end);
    if (_visualize)
    {
        for (const auto& node: path_nodes)
        {
            _graph[node].tag(kmint::graph::node_tag::path);
        }
    }

    std::vector<node_type*> path{};
    for (const auto& node: path_nodes) path.push_back(&_graph[node]);
    return path;
}

std::map<std::size_t, Node> AStar::find_visited(const node_type& begin, const node_type& end) const noexcept
{
    std::map<std::size_t, Node> nodes{};
    for (const node_type& graphNode: _graph)
    {
        nodes.emplace(graphNode.node_id(), Node{
                &graphNode, std::make_pair(_graph.num_nodes(), DBL_MAX)
        });
    }
    nodes[begin.node_id()].weight = std::make_pair(begin.node_id(), 0);
    std::priority_queue<Node> unvisited{};
    unvisited.push(nodes[begin.node_id()]);

    for (; !unvisited.empty(); unvisited.pop())
    {
        const auto node = unvisited.top();

        if (node.node->node_id() == end.node_id())
        {
            break;
        }

        for (int i = 0; i < node.node->num_edges(); ++i)
        {
            auto& edge = node.node->operator[](i);
            auto& edgeNode = nodes[edge.to().node_id()];

            double nextWeight = edge.weight() + node.weight.second;
            if (nextWeight < edgeNode.weight.second)
            {
                edgeNode.weight = std::make_pair(node.node->node_id(), nextWeight);

                if (!edgeNode.tagged)
                {
                    edgeNode.heuristic = calculate_heuristic(*edgeNode.node, end);
                    edgeNode.tagged = true;
                    unvisited.push(edgeNode);
                }
            }
        }

        nodes[node.node->node_id()].visited = true;
    }

    return nodes;
}

std::vector<std::size_t> AStar::find_path(std::map<std::size_t, Node>& nodes, const node_type& end) const noexcept
{
    std::size_t node = end.node_id();
    std::vector<std::size_t> path{};
    path.push_back(node);
    while (nodes[node].weight.first != node)
    {
        node = nodes[node].weight.first;
        if (nodes.count(node) == 0) return path;
        path.push_back(node);
    }

    return path;
}

double AStar::calculate_heuristic(const node_type& origin, const node_type& destination) const noexcept
{
    auto diffX = destination.location().x() - origin.location().x();
    auto diffY = destination.location().y() - origin.location().y();
    diffX = abs(diffX) / 32;
    diffY = abs(diffY) / 32;

    return sqrt(diffX * diffX + diffY * diffY);
}
