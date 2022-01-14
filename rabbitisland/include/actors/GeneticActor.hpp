#ifndef KMINT_ASSESSMENT_GENETICACTOR_HPP
#define KMINT_ASSESSMENT_GENETICACTOR_HPP

#include "kmint/random.hpp"
#include "kmint/play.hpp"
#include "kmint/rabbitisland/node_algorithm.hpp"
#include "ForceDrivenActor.hpp"
#include "WaterNodeActor.hpp"
#include "HoleNodeActor.hpp"
#include "GrassNodeActor.hpp"

namespace actors
{
    using Graph = kmint::map::map_graph;

    template<class Ty_>
    class GeneticActor : public ForceDrivenActor
    {
        private:
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
            GeneticActor(const kmint::math::vector2d& location, kmint::scalar mass, kmint::scalar maxVelocity, const kmint::play::actor& dog) : ForceDrivenActor(location, mass, maxVelocity),
                                                                                                                                                                                                                           _dog(dog)
            {
                attractionDog = kmint::random_scalar(-1, 1);
                attractionWater = kmint::random_scalar(-1, 1);
                attractionGrass = kmint::random_scalar(-1, 1);
                attractionHoles = kmint::random_scalar(-1, 1);
                cohesion = kmint::random_scalar(0, 1);
                separation = kmint::random_scalar(0, 1);
                alignment = kmint::random_scalar(0, 1);
                separation = 1;
            }

            void act(kmint::delta_time dt) override
            {
                ForceDrivenActor::act(dt);

                kmint::math::vector2d dogVector{0, 0};
                kmint::math::vector2d waterVector{0, 0};
                kmint::math::vector2d grassVector{0, 0};
                kmint::math::vector2d holesVector{0, 0};
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
                    if (&*it == &_dog)
                    {
                        dogVector += (_dog.location() - location());
                    }
                    if (auto const* water = dynamic_cast<WaterNodeActor const*>(&*it); water)
                    {
                        waterVector += (water->location() - location());
                    }
                    if (auto const* hole = dynamic_cast<HoleNodeActor const*>(&*it); hole)
                    {
                        holesVector += (hole->location() - location());
                    }
                    if (auto const* grass = dynamic_cast<GrassNodeActor const*>(&*it); grass)
                    {
                        grassVector += (grass->location() - location());
                    }
                }

                dogVector *= attractionDog;
                waterVector *= attractionWater;
                grassVector *= attractionGrass;
                holesVector *= attractionHoles;
                cohesionVector *= cohesion;
                separationVector *= separation;
                alignmentVector *= alignment;

                kmint::math::vector2d force{0, 0};

                force += (dogVector) * 8;
                force += (waterVector) * 15;
                force += (grassVector) * 10;
                force += (holesVector) * 15;
                force += (cohesionVector) * 3;
                force += (separationVector) * 125;
                force += (alignmentVector) * 0.5;

                ApplyForce(force, dt);
            }

            [[nodiscard]] kmint::scalar perception_range() const override
            {
                return 128.0f;
            }
    };
}

#endif //KMINT_ASSESSMENT_GENETICACTOR_HPP
