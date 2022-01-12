#ifndef KMINT_ASSESSMENT_COLLIDABLENODEACTOR_HPP
#define KMINT_ASSESSMENT_COLLIDABLENODEACTOR_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "kmint/rabbitisland/resources.hpp"

namespace actors
{
    class CollidableNodeActor : public kmint::play::free_roaming_actor
    {
        private:
            kmint::play::image_drawable _drawable;

        public:
            explicit CollidableNodeActor(const kmint::map::map_node& node) : free_roaming_actor(node.location()),
                                                                             _drawable(*this, kmint::graphics::image(kmint::rabbitisland::InvisibleImage()))
            {
            }

            [[nodiscard]] const kmint::ui::drawable& drawable() const override
            {
                return _drawable;
            }

            [[nodiscard]] kmint::scalar collision_range() const override
            {
                return 16;
            }

            [[nodiscard]] bool incorporeal() const override
            {
                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_COLLIDABLENODEACTOR_HPP
