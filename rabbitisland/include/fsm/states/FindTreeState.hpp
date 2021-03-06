#ifndef KMINT_ASSESSMENT_FINDTREESTATE_HPP
#define KMINT_ASSESSMENT_FINDTREESTATE_HPP

#include "fsm/states/PathFindState.hpp"
#include "algorithms/Node.hpp"
#include "kmint/rabbitisland/dog.hpp"

namespace fsm::states
{
    class FindTreeState : public PathFindState<kmint::rabbitisland::dog>
    {
        public:
            FindTreeState(kmint::rabbitisland::dog* data, graph_type& graph) : PathFindState<kmint::rabbitisland::dog>(data, graph)
            {
            }

            void AfterEnter() override
            {
                Data()->IsHunting(false);
                Data()->SetTint(kmint::graphics::color{119, 77, 43});
            }

            void AfterExit() override
            {
                Data()->RemoveTint();
            }

            void SetTarget() override
            {
                if (_target == nullptr || _target->node_info().kind != 'T')
                {
                    _target = &kmint::rabbitisland::find_node_of_kind(_graph, 'T');
                }
            }

            void AfterStep() override
            {
                Data()->UseThirst();
            }
    };
}

#endif //KMINT_ASSESSMENT_FINDTREESTATE_HPP
