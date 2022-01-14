#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/rabbitisland/rabbit.hpp"

#include "fsm/states/States.hpp"
#include "fsm/transitions/Transitions.hpp"

#include "consts.hpp"

#include <iostream>
#include <algorithm>

using namespace fsm::states;
using namespace fsm::transitions;

namespace kmint::rabbitisland
{
    using DogState = fsm::State<dog>;
    using SharedDogState = std::shared_ptr<DogState>;

    dog::dog(map::map_graph& g, map::map_node& initial_node, const mister& mister, const misses& misses, RabbitManager* rabbitManager) : play::map_bound_actor(initial_node),
                                                                                                           drawable_(*this, graphics::image(dog_image())),
                                                                                                           _isHunting(true),
                                                                                                           _thirst(0),
                                                                                                           _timesDrank(0),
                                                                                                           _rabbitManager(rabbitManager),
                                                                                                           _drinks{},
                                                                                                           _thirstRandomValue(0),
                                                                                                           _thirstCurrentValue(0)

    {
        _drinks.emplace(&mister, std::make_pair(0, 0));
        _drinks.emplace(&misses, std::make_pair(0, 0));

        auto wanderState = std::make_shared<WanderState<dog>>(this);
        auto huntState = std::make_shared<HuntRabbitState>(this, g);
        auto scaredState = std::make_shared<ScaredDogState>(this);
        auto thirstState = std::make_shared<ThirstyDogState>(this);
        auto findTreeState = std::make_shared<FindTreeState>(this, g);
        auto sleepState = std::make_shared<FreezeState<dog>>(this);
        auto findMisterState = std::make_shared<FindActorState>(this, g, &mister);
        auto findMissesState = std::make_shared<FindActorState>(this, g, &misses);

        auto wanderHuntTransition = std::make_shared<LambdaTransition<dog>>(huntState, [](const SharedDogState& state) { return state->Data()->NearbyRabbits() > 0; });
        auto huntWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const SharedDogState& state) { return state->Data()->NearbyRabbits() == 0; });
        auto dogThirstTransition = std::make_shared<LambdaTransition<dog>>(thirstState, [](const SharedDogState& state) { return state->Data()->Thirst() == 100; });
        auto thirstWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const SharedDogState& state) { return state->Data()->Thirst() != 100; });
        auto scaredTransition = std::make_shared<LambdaTransition<dog>>(scaredState, [](const SharedDogState& state) { return state->Data()->NearbyRabbits() > 10; });
        auto scaredWanderTransition = std::make_shared<LambdaTransition<dog>>(wanderState, [](const SharedDogState& state) {
            auto scaredState = std::dynamic_pointer_cast<WanderState<dog>>(state);
            return scaredState->Steps() >= 10;
        });
        auto thirstTreeTransition = std::make_shared<LambdaTransition<dog>>(findTreeState, [](const SharedDogState& state) { return state->Data()->TimesDrank() == 2; });
        auto treeFoundSleepTransition = std::make_shared<LambdaTransition<dog>>(sleepState, [](const SharedDogState& state) { return state->Data()->node().node_info().kind == 'T'; });
        auto sleepWanderTransition = std::make_shared<SleepWanderTransition<dog>>(wanderState);
        auto thirstMisterTransition = std::make_shared<ProbablisticTransition<dog>>(findMisterState, _thirstCurrentValue, _thirstRandomValue, [this, &mister]() { return DrinkChance(&mister); });
        auto thirstMissesTransition = std::make_shared<ProbablisticTransition<dog>>(findMissesState, _thirstCurrentValue, _thirstRandomValue, [this, &misses]() { return DrinkChance(&misses); });

        wanderState->AddTransition(wanderHuntTransition);
        wanderState->AddTransition(scaredTransition);
        wanderState->AddTransition(dogThirstTransition);

        huntState->AddTransition(huntWanderTransition);
        huntState->AddTransition(scaredTransition);
        huntState->AddTransition(dogThirstTransition);

        scaredState->AddTransition(dogThirstTransition);
        scaredState->AddTransition(scaredWanderTransition);

        thirstState->AddTransition(thirstMisterTransition);
        thirstState->AddTransition(thirstMissesTransition);

        findMisterState->AddTransition(thirstTreeTransition);
        findMisterState->AddTransition(thirstWanderTransition);

        findMissesState->AddTransition(thirstTreeTransition);
        findMissesState->AddTransition(thirstWanderTransition);

        findTreeState->AddTransition(treeFoundSleepTransition);

        sleepState->AddTransition(sleepWanderTransition);

        AddState(wanderState);
        AddState(huntState);
        AddState(scaredState);
        AddState(thirstState);
        AddState(findMisterState);
        AddState(findMissesState);
        AddState(findTreeState);
        AddState(sleepState);
    }

    void dog::act(delta_time dt)
    {
        StateTick(dt);

        if (IsHunting())
        {
            for (auto i = begin_collision(); i != end_collision(); ++i)
            {
                auto& a = *i;
                if (auto* p = dynamic_cast<rabbit*>(&a); p)
                {
                    std::cout << "See you.." << a.location().x() << ", " << a.location().y() << "\n";
                    p->Kill();
                }
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
                auto nDistance = math::distance(location(), p->location());
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

    void dog::ThirstRandom()
    {
        _thirstCurrentValue = 0;
        _thirstRandomValue = kmint::random_scalar(0, 1);
    }

    void dog::Drink(int amount, play::actor* feeder)
    {
        _thirst -= amount;
        if (_thirst < 0) _thirst = 0;
        ++_timesDrank;

        _drinks[feeder].first++;
        _drinks[feeder].second += amount;
    }

    double dog::DrinkChance(const play::actor* feeder)
    {
        if (std::any_of(_drinks.begin(), _drinks.end(), [](const auto& item) { return item.second.first < 1; }))
        {
            return 1.0f / _drinks.size();
        }

        double totalDrinks{0};
        double totalWater{0};
        for (const auto& item: _drinks)
        {
            totalDrinks += item.second.first;
            totalWater += item.second.second;
        }
        double avgWater = totalWater / totalDrinks;
        double avgFeederWater = _drinks[feeder].second / _drinks[feeder].first;

        return 1 / avgWater * avgFeederWater;
    }

    int dog::TimesDrank() const
    {
        return _timesDrank;
    }

    void dog::Sleep()
    {
        _timesDrank = 0;
        _rabbitManager->Revive(*this);
    }

} // namespace kmint
