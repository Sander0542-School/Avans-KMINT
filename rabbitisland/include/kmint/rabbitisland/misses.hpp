#ifndef KMINT_RABBITISLAND_MISSES_HPP
#define KMINT_RABBITISLAND_MISSES_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "fsm/StateMachine.hpp"

#include "consts.hpp"
namespace kmint::rabbitisland
{
    class misses : public play::map_bound_actor, public fsm::StateMachine<misses>
    {
        public:
            misses(map::map_graph& g, map::map_node& initial_node);

            // wordt elke game tick aangeroepen
            void act(delta_time dt) override;

            [[nodiscard]] ui::drawable const& drawable() const override
            {
                return drawable_;
            }

            // als incorporeal false is, doet de actor mee aan collision detection
            [[nodiscard]] bool incorporeal() const override
            {
                return false;
            }

            // geeft de lengte van een zijde van de collision box van deze actor terug.
            // Belangrijk voor collision detection
            [[nodiscard]] scalar collision_range() const override
            {
                return 16.0;
            }

            // geeft aan dat de misses andere actors kan zien
            [[nodiscard]] bool perceptive() const override
            {
                return true;
            }

            // geeft het bereik aan waarbinnen een misses
            // andere actors kan waarnemen.
            [[nodiscard]] scalar perception_range() const override
            {
                return MissesScareRadius;
            }


            [[nodiscard]] bool IsRabbitNearby() const;

            void SetTint(kmint::graphics::color tint)
            {
                drawable_.set_tint(tint);
            }

            void RemoveTint()
            {
                drawable_.remove_tint();
            }

        private:
            // hoeveel tijd is verstreken sinds de laatste beweging
            delta_time t_passed_{};
            // weet hoe de koe getekend moet worden
            play::image_drawable drawable_;
    };

} // namespace kmint

#endif /* KMINT_RABBITISLAND_MISSES_HPP */
