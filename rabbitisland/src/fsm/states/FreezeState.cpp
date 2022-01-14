#include "fsm/states/FreezeState.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/dog.hpp"

using namespace kmint::rabbitisland;
using namespace fsm::states;

template<>
void FreezeState<mister>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
    Data()->SetTint(kmint::graphics::color{119, 135, 147});
}

template<>
void FreezeState<mister>::Exit()
{
    Data()->RemoveTint();
}

template<>
void FreezeState<misses>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
    Data()->SetTint(kmint::graphics::color{119, 135, 147});
}

template<>
void FreezeState<misses>::Exit()
{
    Data()->RemoveTint();
}

template<>
void FreezeState<dog>::Enter()
{
    _totalDuration = kmint::from_seconds(0);
    Data()->SetTint(kmint::graphics::color{119, 135, 147});
    Data()->IsHunting(false);
}

template<>
void FreezeState<dog>::Exit()
{
    Data()->Sleep();
    Data()->RemoveTint();
}