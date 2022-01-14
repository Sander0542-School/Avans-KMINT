#include "kmint/rabbitisland/rabbit.hpp"
#include "kmint/rabbitisland/resources.hpp"
#include "kmint/random.hpp"
#include "actors/WaterNodeActor.hpp"
#include "actors/HoleNodeActor.hpp"

namespace kmint::rabbitisland
{
    rabbit::rabbit(const play::actor& dog) : actors::GeneticActor<rabbit>(random_location(), RabbitMass, RabbitMaxVelocity, dog),
                                                                                                                                                   drawable_(*this, rabbit_image()),
                                                                                                                                                   alive{true}
    {
    }

    math::vector2d rabbit::random_location()
    {
        return {random_scalar(96, 960), random_scalar(160, 704)};
    }

    void rabbit::act(delta_time dt)
    {
        actors::GeneticActor<rabbit>::act(dt);

        for (auto i = begin_collision(); i != end_collision(); ++i)
        {
            auto const& a = *i;
            if (auto const* p = dynamic_cast<actors::WaterNodeActor const*>(&a); p)
            {
                std::cout << "Drowning.." << a.location().x() << ", " << a.location().y() << "\n";
                alive = false;
            }
            if (auto const* p = dynamic_cast<actors::HoleNodeActor const*>(&a); p)
            {
                std::cout << "Hiding.." << a.location().x() << ", " << a.location().y() << "\n";
                alive = false;
            }
        }
    }

} // namespace kmint
