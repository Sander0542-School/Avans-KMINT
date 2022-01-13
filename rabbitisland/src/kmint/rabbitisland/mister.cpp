#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"

#include "consts.hpp"
#include "fsm/fsm.hpp"

namespace kmint::rabbitisland
{
    mister::mister(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{initial_node}, drawable_{*this, graphics::image{mister_image()}}
    {
        auto wanderState = std::make_shared<fsm::states::WanderState<mister>>(this);
        auto photographState = std::make_shared<fsm::states::FreezeState<mister>>(this);

        AddState(wanderState);
        AddState(photographState);

        auto wanderPhotographTransition = std::make_shared<fsm::transitions::WanderPhotographTransition<mister>>(photographState, MisterWanderTime * Period);
        auto photographWanderTransition = std::make_shared<fsm::transitions::PhotographWanderTransition<mister>>(wanderState, MisterPhotographTime * Period);
        wanderState->AddTransition(wanderPhotographTransition);
        photographState->AddTransition(photographWanderTransition);
    }

    void mister::act(delta_time dt)
    {
        StateTick(dt);

        for (auto i = begin_collision(); i != end_collision(); ++i)
        {
            if (auto* p = dynamic_cast<dog*>(&*i); p && p->Thirst() == 100)
            {
                const auto water = random_int(30, 50);
                p->Drink(water);
                std::cout << "Mister is feeding dog.. (" << water << ")\n";
            }
        }
    }
}
