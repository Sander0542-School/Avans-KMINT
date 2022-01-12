#ifndef KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP
#define KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP

#include "algorithms/AStar.hpp"

#include "fsm/State.hpp"

#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"

namespace fsm::states
{
    class HuntRabbitState : public State<kmint::rabbitisland::dog>
    {
        private:
            kmint::delta_time _timePassed{};
            const node_type* _target;
            std::vector<node_type*> _path{};
            graph_type& _graph;
            std::unique_ptr<algorithms::PathAlgo> _pathAlgo;

        public:
            HuntRabbitState(kmint::rabbitisland::dog* data, graph_type& graph) : State<kmint::rabbitisland::dog>(data),
                                                                                 _graph{graph},
                                                                                 _target{nullptr}
            {
                _pathAlgo = std::make_unique<algorithms::AStar>(_graph, true);
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;
                if (const auto* rabbit = Data()->nearest_rabbit(); rabbit)
                {
                    _target = &kmint::rabbitisland::find_closest_node_to(_graph, rabbit->location());
                }
                if (Data() != nullptr && _target != nullptr)
                {
                    if (_path.empty() || _path[0]->node_id() != _target->node_id())
                    {
                        _path = _pathAlgo->find(Data()->node(), *_target);
                    }

                    if (kmint::to_seconds(_timePassed) < Data()->node_time()) return;

                    if (_path.size() > 1)
                    {
                        _path.pop_back();
                        Data()->node(*_path.back());
                    }
                }

                _timePassed = kmint::from_seconds(0);
            }

            void Enter() override
            {
                Data()->isHunting(true);
                _timePassed = kmint::from_seconds(0);
            }

            void Exit() override
            {
                _graph.untag_all();
                _path.clear();
            }
    };
}

#endif //KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP
