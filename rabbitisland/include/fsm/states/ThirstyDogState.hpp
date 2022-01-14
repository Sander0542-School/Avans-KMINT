#ifndef KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP
#define KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP

#include "fsm/State.hpp"

namespace fsm::states
{
    class ThirstyDogState : public State<kmint::rabbitisland::dog>
    {
        public:
            explicit ThirstyDogState(kmint::rabbitisland::dog* data) : State<kmint::rabbitisland::dog>(data)
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                Data()->ThirstRandom();
            }

            void Enter() override
            {
                Data()->IsHunting(false);
                Data()->SetTint(kmint::graphics::color{0, 0, 255});
            }

            void Exit() override
            {
                Data()->RemoveTint();
            }
    };
}

#endif //KMINT_ASSESSMENT_THIRSTYDOGSTATE_HPP
