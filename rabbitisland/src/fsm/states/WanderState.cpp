#include "fsm/states/WanderState.hpp"

#include "kmint/rabbitisland/dog.hpp"

using namespace fsm::states;
using namespace kmint::rabbitisland;

template<typename Ty_>
double WanderState<Ty_>::StepDuration() const
{
    return Period;
}

template<typename Ty_>
void WanderState<Ty_>::Enter()
{
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
}

template<typename Ty_>
void WanderState<Ty_>::HandleStep()
{
}

template<>
void WanderState<dog>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    Data()->IsHunting(true);
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
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
