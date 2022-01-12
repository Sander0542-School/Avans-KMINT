#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/rabbitisland/rabbit.hpp"

#include "fsm/fsm.hpp"

namespace kmint::rabbitisland
{
    misses::misses(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{initial_node},
                                                                     drawable_{*this, graphics::image{misses_image()}}
    {
        auto wanderState = std::make_shared<fsm::states::WanderState<misses>>(this);
        auto freezeState = std::make_shared<fsm::states::FreezeState<misses>>(this);

        AddState(wanderState);
        AddState(freezeState);

        auto wanderScaredFromBunnyTransition = std::make_shared<fsm::transitions::WanderScaredFromBunnyTransition<misses>>(freezeState);
        auto scaredFromBunnyWanderTransition = std::make_shared<fsm::transitions::ScaredFromBunnyWanderTransition<misses>>(wanderState);
        wanderState->AddTransition(wanderScaredFromBunnyTransition);
        freezeState->AddTransition(scaredFromBunnyWanderTransition);
    }

    void misses::act(delta_time dt)
    {
        StateTick(dt);
    }

    bool misses::IsRabbitNearby() const
    {
        for (auto i = begin_perceived(); i != end_perceived(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<rabbit const*>(&a); p)
            {
                return true;
            }
        }

        return false;
    }
} // namespace kmint
