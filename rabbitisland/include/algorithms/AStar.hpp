#ifndef KMINTAPP_ASTAR_HPP
#define KMINTAPP_ASTAR_HPP

#include "algorithms/PathAlgo.hpp"

namespace algorithms
{
    class AStar : public PathAlgo
    {
        private:
            [[nodiscard]] std::map<std::size_t, Node> find_visited(const node_type& begin, const node_type& end) const noexcept;

            std::vector<std::size_t> find_path(std::map<std::size_t, Node>& nodes, const node_type& end) const noexcept;

            [[nodiscard]] double calculate_heuristic(const node_type& origin, const node_type& destination) const noexcept;

        public:
            explicit AStar(graph_type& graph, bool visualize = false);

            [[nodiscard]] std::vector<node_type*> find(const node_type& begin, const node_type& end) const noexcept override;
    };
}

#endif //KMINTAPP_ASTAR_HPP
