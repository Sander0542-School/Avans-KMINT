#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/dog.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint::rabbitisland
{
    rabbit::rabbit() : actors::ForceDrivenActor{random_location()}, drawable_{*this, rabbit_image()}, alive{true}
    {
    }

    math::vector2d rabbit::random_location()
    {
        return {random_scalar(96, 960), random_scalar(160, 704)};
    }

    void rabbit::act(delta_time dt)
    {
        scalar min{-(RabbitMaxVelocity / 2)};
        scalar max{(RabbitMaxVelocity / 2)};
        math::vector2d force{random_scalar(min, max), random_scalar(min, max)};

        ApplyForce(force, dt);

        // wanneer een konijn collide met de hond, is het konijn dood
        for (auto i = begin_collision(); i != end_collision(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<dog const*>(&a); p && p->IsHunting())
            {
                std::cout << "See you.." << a.location().x() << ", " << a.location().y() << "\n";
                alive = false;
            }
        }
    }

} // namespace kmint
