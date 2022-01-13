#ifndef KMINT_RABBITISLAND_MISTER_HPP
#define KMINT_RABBITISLAND_MISTER_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "fsm/StateMachine.hpp"
#include "dog.hpp"

namespace kmint::rabbitisland
{

    class mister : public play::map_bound_actor, public fsm::StateMachine<mister>
    {
        public:
            mister(map::map_graph& g, map::map_node& initial_node, dog& dog);

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
            scalar collision_range() const override
            {
                return 16.0;
            }

        private:
            // hoeveel tijd is verstreken sinds de laatste beweging
            delta_time t_passed_{};
            // weet hoe de koe getekend moet worden
            play::image_drawable drawable_;
            dog& _dog;
    };

} // namespace kmint

#endif /* KMINT_RABBITISLAND_MISTER_HPP */
