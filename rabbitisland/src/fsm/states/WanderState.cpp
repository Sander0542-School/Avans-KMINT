#include "fsm/states/WanderState.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/dog.hpp"

using namespace fsm::states;
using namespace kmint::rabbitisland;

template<>
void WanderState<dog>::AfterEnter()
{
    Data()->SetTint(kmint::graphics::color{61, 153, 0});
    Data()->IsHunting(true);
}

template<>
void WanderState<dog>::Exit()
{
    Data()->RemoveTint();
}

template<>
void WanderState<dog>::HandleStep()
{
    Data()->UseThirst();
}

template<>
void WanderState<mister>::Exit()
{
    Data()->RemoveTint();
}

template<>
void WanderState<mister>::AfterEnter()
{
    Data()->SetTint(kmint::graphics::color{61, 153, 0});
}

template<>
void WanderState<mister>::HandleStep()
{
}

template<>
void WanderState<misses>::Exit()
{
    Data()->RemoveTint();
}

template<>
void WanderState<misses>::AfterEnter()
{
    Data()->SetTint(kmint::graphics::color{61, 153, 0});
}

template<>
void WanderState<misses>::HandleStep()
{
}
