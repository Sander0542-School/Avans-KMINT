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

            void Enter() override
            {
                WanderState::Enter();
//                Data()->SetTint({0, 255, 0, 127});
                Data()->IsHunting(true);
            }

            void Exit() override
            {
                WanderState::Exit();
            }
    };
}

#endif //KMINTAPP_SCAREDDOGSTATE_HPP
