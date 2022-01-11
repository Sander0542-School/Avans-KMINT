#include "fsm/states/WanderState.hpp"

#include "sim/cow.hpp"
#include "sim/hare.hpp"

using namespace fsm::states;

template<>
void WanderState<sim::cow>::Enter()
{
    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<sim::cow>::Exit()
{
    Data()->RemoveTint();
}

template<>
void WanderState<sim::hare>::Enter()
{
    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<sim::hare>::Exit()
{
    Data()->RemoveTint();
}
