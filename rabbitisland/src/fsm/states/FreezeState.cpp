#include "fsm/states/FreezeState.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/mister.hpp"

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
void FreezeState<kmint::rabbitisland::dog>::Exit()
{
    Data()->Sleep();
}