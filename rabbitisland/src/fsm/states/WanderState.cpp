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
void WanderState<Ty_>::Enter()
{
    _timePassed = kmint::from_seconds(0);
    _steps = 0;
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
void WanderState<mister>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _totalDuration = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<mister>::Exit()
{
//    Data()->RemoveTint();
}

template<>
double WanderState<mister>::StepDuration() const
{
    return Period * MisterWanderSpeed;
}

template<>
void WanderState<misses>::Enter()
{
//    Data()->SetTint({0, 255, 0, 127});
    _timePassed = kmint::from_seconds(0);
    _totalDuration = kmint::from_seconds(0);
    _steps = 0;
}

template<>
void WanderState<misses>::Exit()
{
//    Data()->RemoveTint();
}

template<>
double WanderState<misses>::StepDuration() const
{
    return Period * MissesWanderSpeed;
}