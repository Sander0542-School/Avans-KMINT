#ifndef KMINT_ASSESSMENT_GENETICACTOR_HPP
#define KMINT_ASSESSMENT_GENETICACTOR_HPP

#include "kmint/random.hpp"
#include "kmint/play.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "ForceDrivenActor.hpp"
#include "WaterNodeActor.hpp"

namespace actors
{
    using Graph = kmint::map::map_graph;

    template<class Ty_>
    class GeneticActor : public ForceDrivenActor
    {
        private:
            const Graph& _waterGraph;
            const Graph& _grassGraph;
            const Graph& _holesGraph;
            const kmint::play::actor& _dog;

        protected:
            float attractionDog;
            float attractionWater;
            float attractionGrass;
            float attractionHoles;
            float cohesion;
            float separation;
            float alignment;

        public:
            GeneticActor(const kmint::math::vector2d& location, kmint::scalar mass, kmint::scalar maxVelocity, const Graph& waterGraph, const Graph& grassGraph, const Graph& holesGraph, const kmint::play::actor& dog) : ForceDrivenActor(location, mass, maxVelocity),
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
                auto grassVector = (ClosestNode(_grassGraph) - location()) * attractionGrass;
                auto holesVector = (ClosestNode(_holesGraph) - location()) * attractionHoles;
                kmint::math::vector2d waterVector{0, 0};
                kmint::math::vector2d cohesionVector{0, 0};
                kmint::math::vector2d separationVector{0, 0};
                kmint::math::vector2d alignmentVector{0, 0};

                for (auto it = begin_perceived(); it != end_perceived(); ++it)
                {
                    if (auto const* actor = dynamic_cast<GeneticActor<Ty_> const*>(&*it); actor)
                    {
                        cohesionVector += (actor->location() - location());
                        alignmentVector += actor->_velocity;
                        if (kmint::math::distance(location(), actor->location()) < 28)
                        {
                            separationVector += (location() - actor->location());
                        }
                    }
                    if (auto const* water = dynamic_cast<WaterNodeActor const*>(&*it); water)
                    {
                        waterVector += (water->location() - location());
                    }
                }

                waterVector *= attractionWater;
                cohesionVector *= cohesion;
                separationVector *= separation;
                alignmentVector *= alignment;

                kmint::math::vector2d force{0, 0};

                force += (dogVector);
                force += (waterVector) * 15;
                force += (grassVector) * 1;
                force += (holesVector) * 3;
                force += (cohesionVector) * 5;
                force += (separationVector) * 100;
                force += (alignmentVector) * 0.5;

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
