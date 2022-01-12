#include "fsm/states/FreezeState.hpp"
#include "kmint/rabbitisland/mister.hpp"

using namespace fsm::states;

template<>
void FreezeState<kmint::rabbitisland::mister>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
}

template<>
void FreezeState<kmint::rabbitisland::mister>::Exit()
{
}