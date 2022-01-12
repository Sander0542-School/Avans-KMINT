#ifndef KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP
#define KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP

#include "algorithms/AStar.hpp"

#include "fsm/states/PathFindState.hpp"

#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"

namespace fsm::states
{
    class HuntRabbitState : public PathFindState<kmint::rabbitisland::dog>
    {
        public:
            HuntRabbitState(kmint::rabbitisland::dog* data, graph_type& graph) : PathFindState<kmint::rabbitisland::dog>(data, graph)
            {
            }

            void AfterEnter() override
            {
                Data()->IsHunting(true);
            }

            void SetTarget() override
            {
                if (const auto* rabbit = Data()->NearestRabbit(); rabbit)
                {
                    _target = &kmint::rabbitisland::find_closest_node_to(_graph, rabbit->location());
                }
            }

            [[nodiscard]] double NodeWaitingTime() const override
            {
                return Data()->NodeWaitingTime();
            }

            void AfterStep() override
            {
                Data()->UseThirst();
            }
    };
}

#endif //KMINT_ASSESSMENT_HUNTRABBITSTATE_HPP
