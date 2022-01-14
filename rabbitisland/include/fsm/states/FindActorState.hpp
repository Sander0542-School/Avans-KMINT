#ifndef KMINT_ASSESSMENT_FINDACTORSTATE_HPP
#define KMINT_ASSESSMENT_FINDACTORSTATE_HPP

#include "PathFindState.hpp"
#include "kmint/play.hpp"
#include "kmint/rabbitisland/dog.hpp"

namespace fsm::states
{
    class FindActorState : public PathFindState<kmint::rabbitisland::dog>
    {
        private:
            const kmint::play::map_bound_actor* _actor;

        public:
            FindActorState(kmint::rabbitisland::dog* data, graph_type& graph, const kmint::play::map_bound_actor* actor) : PathFindState<kmint::rabbitisland::dog>(data, graph),
                                                                                                                           _actor{actor}
            {
            }

            void AfterEnter() override
            {
                Data()->IsHunting(false);
            }

            void SetTarget() override
            {
                _target = &_actor->node();
            }
    };
}

#endif //KMINT_ASSESSMENT_FINDACTORSTATE_HPP
