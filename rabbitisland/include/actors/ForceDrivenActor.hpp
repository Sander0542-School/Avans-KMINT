#ifndef KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP
#define KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP

#include "kmint/math/vector2d.hpp"
#include "kmint/play.hpp"
#include "consts.hpp"

namespace actors
{
    class ForceDrivenActor : public kmint::play::free_roaming_actor
    {
        protected:
            kmint::math::vector2d _velocity{0, 0};
            const kmint::scalar _mass;
            const kmint::scalar _maxVelocity;

        public:
            explicit ForceDrivenActor(const kmint::math::vector2d& location, kmint::scalar mass, kmint::scalar maxVelocity) : free_roaming_actor(location),
                                                                                                                              _mass(mass),
                                                                                                                              _maxVelocity(maxVelocity)
            {
            }

            void ApplyForce(kmint::math::vector2d force, kmint::delta_time deltaTime)
            {
                auto acceleration = force / _mass;
                auto seconds = kmint::to_seconds(deltaTime);
                _velocity += (acceleration * seconds);

                auto length = std::sqrt(_velocity.x() * _velocity.x() + _velocity.y() * _velocity.y());
                if (length > _maxVelocity)
                {
                    _velocity = _velocity / length * _maxVelocity;
                }

                auto newLocation = location() + (_velocity * seconds);
                location(newLocation);
            }
    };
}

#endif //KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP
