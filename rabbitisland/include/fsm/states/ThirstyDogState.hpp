#ifndef KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP
#define KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP

#include "fsm/states/PathFindState.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"

namespace fsm::states
{
    class ThirstyDogState : public PathFindState<kmint::rabbitisland::dog>
    {
        private:
            const kmint::rabbitisland::mister* _mister;
            const kmint::rabbitisland::misses* _misses;
            bool _trackingMister;

        public:
            ThirstyDogState(kmint::rabbitisland::dog* data, graph_type& graph, const kmint::rabbitisland::mister* mister, const kmint::rabbitisland::misses* misses) : PathFindState(data, graph),
                                                                                                                                                                       _mister{mister},
                                                                                                                                                                       _misses{misses},
                                                                                                                                                                       _trackingMister(true)
            {
            }

            void AfterEnter() override
            {
                _trackingMister = containers::Random::NextBool();
//                Data()->SetTint({0, 255, 0, 127});
                Data()->IsHunting(false);
            }

            void SetTarget() override
            {
                _target = _trackingMister ? &_mister->node() : &_misses->node();
            }

            [[nodiscard]] double NodeWaitingTime() const override
            {
                return Data()->NodeWaitingTime();
            }
    };
}

#endif //KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP
