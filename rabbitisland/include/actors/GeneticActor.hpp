#ifndef KMINT_ASSESSMENT_GENETICACTOR_HPP
#define KMINT_ASSESSMENT_GENETICACTOR_HPP

#include "kmint/random.hpp"
#include "ForceDrivenActor.hpp"

namespace actors
{
    class GeneticActor : public ForceDrivenActor
    {
        protected:
            float attractionDog;
            float attractionWater;
            float attractionGrass;
            float attractionHoles;
            float cohesion;
            float separation;
            float alignment;

        public:
            explicit GeneticActor(const kmint::math::vector2d& location) : ForceDrivenActor(location)
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

                kmint::scalar min{-(RabbitMaxVelocity / 2)};
                kmint::scalar max{(RabbitMaxVelocity / 2)};
                kmint::math::vector2d force{kmint::random_scalar(min, max), kmint::random_scalar(min, max)};

                ApplyForce(force, dt);
            }

        private:
            static bool InRange(float value, float min = -1, float max = 1)
            {
                return value >= min && value <= max;
            }
    };
}

#endif //KMINT_ASSESSMENT_GENETICACTOR_HPP
