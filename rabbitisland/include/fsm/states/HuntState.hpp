#ifndef KMINTAPP_HUNTSTATE_HPP
#define KMINTAPP_HUNTSTATE_HPP

#include "fsm/State.hpp"
#include "algorithms/AStar.hpp"

#include "sim/hare.hpp"

namespace fsm::states
{
    template<typename TData, typename TTarget>
    class HuntState : public fsm::State<TData>
    {
        private:
            kmint::delta_time _timePassed{};
            TTarget* _target;
            std::vector<node_type*> _path{};
            graph_type& _graph;
            std::unique_ptr<algorithms::PathAlgo> _pathAlgo;

        public:
            explicit HuntState(TData* data, TTarget* target, graph_type& graph) : State<TData>(data),
                                                                                  _target{target},
                                                                                  _graph{graph}
            {
                _pathAlgo = std::make_unique<algorithms::AStar>(_graph, true);
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;

                if (this->Data() != nullptr)
                {
                    if (_path.empty() || _path[0]->node_id() != _target->node().node_id())
                    {
                        _path = _pathAlgo->find(this->Data()->node(), _target->node());
                    }

                    if (kmint::to_seconds(_timePassed) < 1) return;

                    if (_path.size() >= 2)
                    {
                        _path.pop_back();
                        this->Data()->node(*_path.back());
                    }
                }

                _timePassed = kmint::from_seconds(0);
            };

            void Enter() override;

            void Exit() override;
    };
}

#endif //KMINTAPP_HUNTSTATE_HPP
