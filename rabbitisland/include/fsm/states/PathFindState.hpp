#ifndef KMINT_ASSESSMENT_PATHFINDSTATE_HPP
#define KMINT_ASSESSMENT_PATHFINDSTATE_HPP

#include "algorithms/AStar.hpp"
#include "fsm/State.hpp"
#include "consts.hpp"

namespace fsm::states
{
    template<typename Ty_>
    class PathFindState : public State<Ty_>
    {
        private:
            kmint::delta_time _timePassed{};
            std::unique_ptr<algorithms::PathAlgo> _pathAlgo;

        protected:
            graph_type& _graph;
            std::vector<node_type*> _path{};
            const node_type* _target;

            PathFindState(Ty_* data, graph_type& graph) : State<Ty_>(data), _graph{graph}, _target{nullptr}
            {
                _pathAlgo = std::make_unique<algorithms::AStar>(_graph, true);
            }

        public:
            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;
                SetTarget();
                if (this->Data() != nullptr && _target != nullptr)
                {
                    if (_path.empty() || _path[0]->node_id() != _target->node_id())
                    {
                        _path = _pathAlgo->find(this->Data()->node(), *_target);
                    }

                    if (kmint::to_seconds(_timePassed) < NodeWaitingTime()) return;

                    if (_path.size() > 1)
                    {
                        _path.pop_back();
                        this->Data()->node(*_path.back());
                        AfterStep();
                    }
                }

                _timePassed = kmint::from_seconds(0);
            }

            void Enter() override
            {
                _timePassed = kmint::from_seconds(0);

                AfterEnter();
            }

            void Exit() override
            {
                _graph.untag_all();
                _path.clear();
                _target = nullptr;

//                this->Data()->RemoveTint();
                AfterExit();
            }

            virtual void AfterEnter()
            {
            }

            virtual void AfterExit()
            {
            }

            virtual void SetTarget() = 0;

            [[nodiscard]] virtual double NodeWaitingTime() const
            {
                return kmint::rabbitisland::waiting_time(this->Data()->node()) * Period;
            };

            virtual void AfterStep()
            {
            }
    };
}

#endif //KMINT_ASSESSMENT_PATHFINDSTATE_HPP
