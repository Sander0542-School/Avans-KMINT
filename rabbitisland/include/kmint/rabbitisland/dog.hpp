#ifndef KMINT_RABBITISLAND_DOG_HPP
#define KMINT_RABBITISLAND_DOG_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "fsm/StateMachine.hpp"
#include "kmint/rabbitisland/misses.hpp"
#include "kmint/rabbitisland/mister.hpp"
#include <map>

namespace kmint::rabbitisland
{
    class rabbit;

    class dog : public play::map_bound_actor, public fsm::StateMachine<dog>
    {
        public:
            dog(map::map_graph& g, map::map_node& initial_node, const mister& mister, const misses& misses);

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
                return 32.0;
            }

            // geeft aan dat de hond andere actors kan zien
            [[nodiscard]] bool perceptive() const override
            {
                return true;
            }

            // geeft het bereik aan waarbinnen een haai
            // andere actors kan waarnemen.
            [[nodiscard]] scalar perception_range() const override
            {
                return 100.f;
            }

            [[nodiscard]] double NodeWaitingTime() const;

            [[nodiscard]] int NearbyRabbits() const;

            [[nodiscard]] const rabbit* NearestRabbit() const;

            [[nodiscard]] bool IsHunting() const;

            void IsHunting(bool isHunting);

            [[nodiscard]] int Thirst() const;

            void Drink(int amount, play::actor* feeder);

            double DrinkChance(const play::actor* feeder);

            void UseThirst();

            [[nodiscard]] int TimesDrank() const;

            void Sleep();

        private:
            // hoeveel tijd is verstreken sinds de laatste beweging
            delta_time t_passed_{};
            // weet hoe de hond getekend moet worden
            play::image_drawable drawable_;
            bool _isHunting;
            int _thirst;
            int _timesDrank;
            std::map<const play::actor*, std::pair<double, double>> _drinks;
            double _thirstRandomValue;
            double _thirstCurrentValue;
    };

} // namespace kmint

#endif /* KMINT_RABBITISLAND_DOG_HPP */
