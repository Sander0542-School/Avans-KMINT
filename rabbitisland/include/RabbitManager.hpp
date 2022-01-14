#ifndef KMINT_ASSESSMENT_RABBITMANAGER_HPP
#define KMINT_ASSESSMENT_RABBITMANAGER_HPP

#include "kmint/play.hpp"
#include "kmint/rabbitisland/rabbit.hpp"

class RabbitManager
{
    private:
        kmint::play::stage& _stage;

    public:
        explicit RabbitManager(kmint::play::stage& stage) : _stage(stage)
        {
        }

        void Revive(kmint::play::actor& dog)
        {
            for (auto i = _stage.begin(); i != _stage.end(); ++i)
            {
                if (auto* rabbit = dynamic_cast<kmint::rabbitisland::rabbit*>(&*i); rabbit)
                {
                    rabbit->Revive();
                }
            }
        }
};

#endif //KMINT_ASSESSMENT_RABBITMANAGER_HPP
