#include "fsm/states/PhotographState.hpp"
#include "kmint/rabbitisland/mister.hpp"

using namespace fsm::states;

template<>
void PhotographState<kmint::rabbitisland::mister>::Enter()
{
    _timePassed = kmint::from_seconds(0);
    _totalDuration = kmint::from_seconds(0);
}

template<>
void PhotographState<kmint::rabbitisland::mister>::Exit()
{
}