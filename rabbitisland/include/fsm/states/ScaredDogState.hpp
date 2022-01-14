#ifndef KMINTAPP_SCAREDDOGSTATE_HPP
#define KMINTAPP_SCAREDDOGSTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"
#include "fsm/states/WanderState.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    class ScaredDogState : public WanderState<kmint::rabbitisland::dog>
    {
        public:
            explicit ScaredDogState(kmint::rabbitisland::dog* data) : WanderState<kmint::rabbitisland::dog>(data)
            {
            }

            void AfterEnter() override
            {
                WanderState::AfterEnter();
                Data()->SetTint({242, 0, 0});
                Data()->IsHunting(false);
            }

            void Exit() override
            {
                WanderState::Exit();
                Data()->RemoveTint();
            }
    };
}

#endif //KMINTAPP_SCAREDDOGSTATE_HPP
