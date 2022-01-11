#include "fsm/states/WanderState.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"

using namespace fsm::states;

template<>
void WanderState<kmint::rabbitisland::mister>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<kmint::rabbitisland::mister>::Exit()
{
//    Data()->RemoveTint();
}

template<>
void WanderState<kmint::rabbitisland::misses>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<kmint::rabbitisland::misses>::Exit()
{
//    Data()->RemoveTint();
}
