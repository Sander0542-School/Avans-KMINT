#ifndef KMINT_ASSESSMENT_GENETICACTOR_HPP
#define KMINT_ASSESSMENT_GENETICACTOR_HPP

#include "kmint/random.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "ForceDrivenActor.hpp"

namespace actors
{
    using Graph = kmint::map::map_graph;

    class GeneticActor : public ForceDrivenActor
    {
        private:
            const Graph& _waterGraph;
            const Graph& _grassGraph;
            const Graph& _holesGraph;
            const kmint::rabbitisland::dog& _dog;

        protected:
            float attractionDog;
            float attractionWater;
            float attractionGrass;
            float attractionHoles;
            float cohesion;
            float separation;
            float alignment;

        public:
            GeneticActor(const kmint::math::vector2d& location, const Graph& waterGraph, const Graph& grassGraph, const Graph& holesGraph, const kmint::rabbitisland::dog& dog) : ForceDrivenActor(location),
                                                                                                                                                                                  _waterGraph(waterGraph),
                                                                                                                                                                                  _grassGraph(grassGraph),
                                                                                                                                                                                  _holesGraph(holesGraph),
                                                                                                                                                                                  _dog(dog)
            {
                attractionDog = kmint::random_scalar(-1, 1);
                attractionWater = kmint::random_scalar(-1, 1);
                attractionGrass = kmint::random_scalar(-1, 1);
                attractionHoles = kmint::random_scalar(-1, 1);
                cohesion = kmint::random_scalar(0, 1);
                separation = kmint::random_scalar(0, 1);
                alignment = kmint::random_scalar(0, 1);
            }

            void act(kmint::delta_time dt) override
            {
                ForceDrivenActor::act(dt);

                auto dogVector = (_dog.location() - location()) * attractionDog;
                auto waterVector = (ClosestNode(_waterGraph) - location()) * attractionDog;
                auto grassVector = (ClosestNode(_grassGraph) - location()) * attractionGrass;
                auto holesVector = (ClosestNode(_holesGraph) - location()) * attractionHoles;

                auto force = dogVector + waterVector + grassVector + holesVector;

                ApplyForce(force, dt);
            }

        private:
            kmint::math::vector2d ClosestNode(const Graph& graph)
            {
                return kmint::rabbitisland::find_closest_node_to(graph, location()).location();
            }
    };
}

#endif //KMINT_ASSESSMENT_GENETICACTOR_HPP
