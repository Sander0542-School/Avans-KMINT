#include "fsm/states/WanderState.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/dog.hpp"

using namespace fsm::states;
using namespace kmint::rabbitisland;

template<typename Ty_>
double WanderState<Ty_>::StepDuration() const
{
    return Period;
}

template<typename Ty_>
void WanderState<Ty_>::AfterEnter()
{
}

template<typename Ty_>
void WanderState<Ty_>::HandleStep()
{
}

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
double WanderState<mister>::StepDuration() const
{
    return Period * MisterWanderSpeed;
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

template<>
double WanderState<misses>::StepDuration() const
{
    return Period * MissesWanderSpeed;
}
