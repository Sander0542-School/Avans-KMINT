#include "fsm/states/FreezeState.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/mister.hpp"

using namespace fsm::states;

template<>
void FreezeState<kmint::rabbitisland::dog>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
    Data()->IsHunting(false);
}

template<>
void FreezeState<kmint::rabbitisland::dog>::Exit()
{
    Data()->Sleep();
}