#ifndef KMINT_ASSESSMENT_PATHALGO_HPP
#define KMINT_ASSESSMENT_PATHALGO_HPP

#include "kmint/graph/basic_node.hpp"
#include "kmint/map/map.hpp"
#include "algorithms/Node.hpp"

#include <map>

namespace algorithms
{
    class PathAlgo
    {
        protected:
            graph_type& _graph;
            bool _visualize;

            PathAlgo(graph_type& graph, bool visualize) : _graph{graph}, _visualize{visualize}
            {
                if (_visualize) _graph.untag_all();
            }

        public:
            virtual std::vector<node_type*> find(const node_type& begin, const node_type& end) const noexcept = 0;
    };
}

#endif //KMINT_ASSESSMENT_PATHALGO_HPP
