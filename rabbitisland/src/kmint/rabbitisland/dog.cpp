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
    using DogState = fsm::State<dog>;
    using SharedDogState = std::shared_ptr<DogState>;

    dog::dog(map::map_graph& g, map::map_node& initial_node, const mister& mister, const misses& misses) : play::map_bound_actor(initial_node),
                                                                                                           drawable_(*this, graphics::image(dog_image())),
                                                                                                           _isHunting(true),
                                                                                                           _thirst(0)
    {
        auto wanderState = std::make_shared<WanderState<dog>>(this);
        auto huntState = std::make_shared<HuntRabbitState>(this, g);
        auto scaredState = std::make_shared<ScaredDogState>(this);

        auto wanderHuntTransition = std::make_shared<LambdaTransition<dog>>(huntState, [](const std::shared_ptr<fsm::State<dog>>& state) { return state->Data()->NearbyRabbits() > 0; });
        auto huntWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const std::shared_ptr<fsm::State<dog>>& state) { return state->Data()->NearbyRabbits() == 0; });

        auto scaredTransition = std::make_shared<LambdaTransition<dog>>(scaredState, [](const std::shared_ptr<fsm::State<dog>>& state) { return state->Data()->NearbyRabbits() > 10; });
        auto scaredWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const std::shared_ptr<fsm::State<dog>>& state) {
        auto thirstState = std::make_shared<ThirstyDogState>(this, g, &mister, &misses);
            auto scaredState = std::dynamic_pointer_cast<WanderState<dog>>(state);
            return scaredState->Steps() >= 10;
        });

        wanderState->AddTransition(wanderHuntTransition);
        wanderState->AddTransition(scaredTransition);
        huntState->AddTransition(huntWanderTransition);
        huntState->AddTransition(scaredTransition);

        AddState(wanderState);
        AddState(huntState);
        AddState(scaredState);
        AddState(thirstState);
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

    double dog::NodeWaitingTime() const
    {
        return waiting_time(node()) * Period;
    }

    int dog::NearbyRabbits() const
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

    const rabbit* dog::NearestRabbit() const
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

    bool dog::IsHunting() const
    {
        return _isHunting;
    }

    void dog::IsHunting(bool isHunting)
    {
        _isHunting = isHunting;
    }

    int dog::Thirst() const
    {
        return _thirst;
    }

    void dog::UseThirst()
    {
        ++_thirst;
        if (_thirst > 100) _thirst = 100;
    }

    void dog::Drink(int amount)
    {
        _thirst -= amount;
        if (_thirst < 0) _thirst = 0;
    }

} // namespace kmint
