#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/rabbitisland/rabbit.hpp"

#include "fsm/states/States.hpp"
#include "fsm/transitions/Transitions.hpp"

#include "consts.hpp"

#include <iostream>

using namespace fsm::states;
using namespace fsm::transitions;

namespace kmint::rabbitisland
{
    dog::dog(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{initial_node}, drawable_{
            *this, graphics::image{
                    dog_image()
            }}
    {
        auto wanderState = std::make_shared<WanderState<dog>>(this, [](const dog* dog1) { return dog1->node_time(); });
        auto huntState = std::make_shared<HuntRabbitState>(this, g);

        auto wanderHuntTransition = std::make_shared<LambdaTransition<dog>>(huntState, [](const std::shared_ptr<fsm::State<dog>>& state) { return state->Data()->nearby_rabbits() > 0; });
        auto huntWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const std::shared_ptr<fsm::State<dog>>& state) { return state->Data()->nearby_rabbits() == 0; });

        wanderState->AddTransition(wanderHuntTransition);
        huntState->AddTransition(huntWanderTransition);

        AddState(wanderState);
        AddState(huntState);
    }

    void dog::act(delta_time dt)
    {
        StateTick(dt);

//        t_passed_ += dt;
//        if (to_seconds(t_passed_) >= waiting_time(node()))
//        {
//            // pick random edge
//            int next_index = random_int(0, node().num_edges());
//            this->node(node()[next_index].to());
//            t_passed_ = from_seconds(0);
//        }

        // laat ook even zien welke konijntjes hij ruikt
        for (auto i = begin_perceived(); i != end_perceived(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<rabbit const*>(&a); p)
            {
                std::cout << "Smelled something at " << a.location().x() << ", " << a.location().y() << "\n";
            }
        }
    }

    double dog::node_time() const
    {
        return waiting_time(node()) * Period;
    }

    int dog::nearby_rabbits() const
    {
        int nearby = 0;

        for (auto i = begin_perceived(); i != end_perceived(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<rabbit const*>(&a); p)
            {
                ++nearby;
            }
        }

        return nearby;
    }

    const rabbit* dog::nearest_rabbit() const
    {
        auto distance = std::numeric_limits<float>::max();
        const rabbit* nearestRabbit = nullptr;

        for (auto i = begin_perceived(); i != end_perceived(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<rabbit const*>(&a); p)
            {
                auto nDistance = distance2(location(), p->location());
                if (nDistance < distance)
                {
                    distance = nDistance;
                    nearestRabbit = p;
                }
            }
        }

        return nearestRabbit;
    }

} // namespace kmint
