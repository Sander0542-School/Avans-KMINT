#ifndef KMINT_ASSESSMENT_RABBITMANAGER_HPP
#define KMINT_ASSESSMENT_RABBITMANAGER_HPP

#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include "actors/WaterNodeActor.hpp"
#include "actors/HoleNodeActor.hpp"

using namespace kmint;

class RabbitManager
{
    private:
        kmint::play::stage* _stage;

    public:
        explicit RabbitManager(kmint::play::stage* stage) : _stage(stage)
        {
        }

        void SpawnRabbits(rabbitisland::dog& dog)
        {
            for (auto i = _stage->begin(); i != _stage->end(); ++i)
            {
                auto const& a = *i;
                if (auto const* p = dynamic_cast<rabbitisland::rabbit const*>(&a); p)
                {
                    _stage->remove_actor(a);
                }
            }

            auto waterMap = rabbitisland::WaterMap();
            auto& waterGraph = waterMap.graph();
            auto grassMap = rabbitisland::GrassMap();
            auto& grassGraph = grassMap.graph();
            auto holesMap = rabbitisland::HolesMap();
            auto& holesGraph = holesMap.graph();

            for (const map::map_node& node: waterGraph)
            {
                _stage->build_actor<actors::WaterNodeActor>(node);
            }
            for (const map::map_node& node: holesGraph)
            {
                _stage->build_actor<actors::HoleNodeActor>(node);
            }

            // Rabbit Create
            for (auto i = 0; i < 100; ++i)
            {
                _stage->build_actor<rabbitisland::rabbit>(waterGraph, grassGraph, holesGraph, dog);
            }
        }
};

#endif //KMINT_ASSESSMENT_RABBITMANAGER_HPP
