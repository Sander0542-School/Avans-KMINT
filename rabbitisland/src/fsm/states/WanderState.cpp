#include "fsm/states/WanderState.hpp"

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
double WanderState<dog>::StepDuration() const
{
    return Data()->NodeWaitingTime() * Period;
}

template<>
void WanderState<dog>::HandleStep()
{
    Data()->UseThirst();
}
