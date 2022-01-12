#include "fsm/states/FreezeState.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/misses.hpp"

using namespace kmint::rabbitisland;
using namespace fsm::states;

template<typename Ty_>
void FreezeState<Ty_>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
}

template<typename Ty_>
void FreezeState<Ty_>::Exit()
{
}

template<>
void FreezeState<mister>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
}

template<>
void FreezeState<mister>::Exit()
{
}

template<>
void FreezeState<misses>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
}

template<>
void FreezeState<misses>::Exit()
{
}