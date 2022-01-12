#ifndef KMINTAPP_WANDERSTATE_HPP
#define KMINTAPP_WANDERSTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    class ScaredDogState : public State<kmint::rabbitisland::dog>
    {
        private:
            kmint::delta_time _timePassed{};
            int _steps = 0;

        public:
            explicit ScaredDogState(kmint::rabbitisland::dog* data) : State<kmint::rabbitisland::dog>(data)
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;

                if (kmint::to_seconds(_timePassed) < Data()->NodeWaitingTime()) return;

                if (this->Data() != nullptr)
                {
                    auto edgeId = containers::Random::Next(0, static_cast<int>(this->Data()->node().num_edges()) - 1);
                    auto& edgeNode = this->Data()->node()[edgeId].to();

                    this->Data()->node(edgeNode);
                    ++_steps;
                }

                _timePassed = kmint::from_seconds(0);
            };

            void Enter() override
            {
//                Data()->SetTint({0, 255, 0, 127});
                Data()->IsHunting(true);
                _timePassed = kmint::from_seconds(0);
                _steps = 0;
            }

            void Exit() override
            {
//                Data()->RemoveTint();
            }

            [[nodiscard]] int Steps() const
            {
                return _steps;
            }
    };
}

#endif //KMINTAPP_WANDERSTATE_HPP
