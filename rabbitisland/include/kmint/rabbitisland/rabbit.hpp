#ifndef KMINT_RABBITISLAND_RABBIT_HPP
#define KMINT_RABBITISLAND_RABBIT_HPP

#include "kmint/play.hpp"
#include "actors/GeneticActor.hpp"
#include <tuple>
#include <vector>

namespace kmint::rabbitisland
{
    class rabbit : public actors::GeneticActor<rabbit>
    {
        public:
            rabbit(const play::actor& dog);

            [[nodiscard]] const ui::drawable& drawable() const override
            {
                return drawable_;
            }

            math::vector2d random_location();

            void act(delta_time dt) override;

            [[nodiscard]] scalar collision_range() const override
            {
                return 32.0f;
            }

            [[nodiscard]] bool must_draw() const override
            {
                return alive;
            }

            [[nodiscard]] bool incorporeal() const override
            {
                return !alive;
            }

            [[nodiscard]] bool perceivable() const override
            {
                return alive;
            }

            [[nodiscard]] bool perceptive() const override
            {
                return alive;
            }

            void Kill()
            {
                alive = false;
            }

            void Revive();

        private:
            play::image_drawable drawable_;
            bool alive;
    };
}

#endif /* KMINT_RABBITISLAND_RABBIT_HPP */
