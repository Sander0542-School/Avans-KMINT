#include "fsm/states/WanderState.hpp"

#include "kmint/rabbitisland/dog.hpp"

using namespace fsm::states;

template<>
void WanderState<kmint::rabbitisland::dog>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    Data()->IsHunting(true);
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<kmint::rabbitisland::dog>::Exit()
{
//    Data()->RemoveTint();
}