#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"

#include "consts.hpp"

#include "fsm/states/WanderState.hpp"

namespace kmint::rabbitisland
{
    misses::misses(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{initial_node},
                                                                     drawable_{*this, graphics::image{misses_image()}}
    {
        AddState(std::make_shared<fsm::states::WanderState<misses>>(this, [](const misses*) { return Period * MissesWanderSpeed; }));
    }

    void misses::act(delta_time dt)
    {
        StateTick(dt);

//        t_passed_ += dt;
//        if (to_seconds(t_passed_) >= 2)
//        {
//            // pick random edge
//            int next_index = random_int(0, node().num_edges());
//            this->node(node()[next_index].to());
//            t_passed_ = from_seconds(0);
//        }
    }
} // namespace kmint
