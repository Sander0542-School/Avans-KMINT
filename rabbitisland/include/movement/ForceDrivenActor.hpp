#ifndef KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP
#define KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP

#include "kmint/math/vector2d.hpp"
#include "kmint/play.hpp"
#include "consts.hpp"

namespace movement
{
    class ForceDrivenActor : public kmint::play::free_roaming_actor
    {
        private:
            kmint::math::vector2d _velocity{};

        public:
            explicit ForceDrivenActor(const kmint::math::vector2d& location) : free_roaming_actor(location)
            {
            }

            void ApplyForce(kmint::math::vector2d force, kmint::delta_time deltaTime)
            {
                auto seconds = kmint::to_seconds(deltaTime);
                _velocity += (force * seconds);

                if (_velocity.x() > RabbitMaxVelocity) _velocity.x(RabbitMaxVelocity);
                if (_velocity.x() < -RabbitMaxVelocity) _velocity.x(-RabbitMaxVelocity);
                if (_velocity.y() > RabbitMaxVelocity) _velocity.y(RabbitMaxVelocity);
                if (_velocity.y() < -RabbitMaxVelocity) _velocity.y(-RabbitMaxVelocity);

                auto newLocation = location() + _velocity;
                location(newLocation);
            }
    };
}

#endif //KMINT_ASSESSMENT_FORCEDRIVENACTOR_HPP
