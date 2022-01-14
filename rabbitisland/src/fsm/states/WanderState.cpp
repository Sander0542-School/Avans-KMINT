#include "fsm/states/WanderState.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/dog.hpp"

using namespace fsm::states;
using namespace kmint::rabbitisland;

template<>
void WanderState<dog>::AfterEnter()
{
//    Data()->SetTint({0, 255, 0, 127});
    Data()->IsHunting(true);
}

template<>
void WanderState<dog>::Exit()
{
//    Data()->RemoveTint();
}

template<>
void WanderState<dog>::HandleStep()
{
    Data()->UseThirst();
}

template<>
void WanderState<mister>::Exit()
{
}

template<>
void WanderState<mister>::AfterEnter()
{
}

template<>
void WanderState<mister>::HandleStep()
{
}

template<>
void WanderState<misses>::Exit()
{
}

template<>
void WanderState<misses>::AfterEnter()
{
}

template<>
void WanderState<misses>::HandleStep()
{
}
