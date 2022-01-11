#include "fsm/states/HuntState.hpp"

#include "sim/cow.hpp"

using namespace fsm::states;

template<>
void HuntState<sim::cow, sim::hare>::Enter()
{
    Data()->SetTint({255, 0, 0, 127});
    _timePassed = kmint::from_seconds(0);
}

template<>
void HuntState<sim::cow, sim::hare>::Exit()
{
    Data()->RemoveTint();
    _graph.untag_all();
    _path.clear();
}
