#ifndef KMINT_ASSESSMENT_RABBITMANAGER_HPP
#define KMINT_ASSESSMENT_RABBITMANAGER_HPP

#include "kmint/play.hpp"
#include "actors/WaterNodeActor.hpp"
#include "actors/HoleNodeActor.hpp"
#include "kmint/rabbitisland/rabbit.hpp"

namespace kmint::rabbitisland
{
    class dog;
}

using namespace kmint;

class RabbitManager
{
    private:
        play::stage& _stage;
        graph::basic_graph<map::map_node_info>& _waterGraph;
        graph::basic_graph<map::map_node_info>& _grassGraph;
        graph::basic_graph<map::map_node_info>& _holesGraph;

    public:
        explicit RabbitManager(play::stage& stage, graph::basic_graph<map::map_node_info>& waterGraph, graph::basic_graph<map::map_node_info>& grassGraph, graph::basic_graph<map::map_node_info>& holesGraph) : _stage(stage),
                                                                                                                                                                                                                 _waterGraph(waterGraph),
                                                                                                                                                                                                                 _grassGraph(grassGraph),
                                                                                                                                                                                                                 _holesGraph(holesGraph)
        {
        }

        void SpawnRabbits(play::actor& dog)
        {
            for (auto i = _stage.begin(); i != _stage.end(); ++i)
            {
                auto& a = *i;
                if (auto* p = dynamic_cast<rabbitisland::rabbit*>(&a); p)
                {
                    p->Kill();
                }
            }

            for (const map::map_node& node: _waterGraph)
            {
                _stage.build_actor<actors::WaterNodeActor>(node);
            }
            for (const map::map_node& node: _holesGraph)
            {
                _stage.build_actor<actors::HoleNodeActor>(node);
            }

            // Rabbit Create
            for (auto i = 0; i < 100; ++i)
            {
                _stage.build_actor<rabbitisland::rabbit>(_waterGraph, _grassGraph, _holesGraph, dog);
            }
        }
};

#endif //KMINT_ASSESSMENT_RABBITMANAGER_HPP
