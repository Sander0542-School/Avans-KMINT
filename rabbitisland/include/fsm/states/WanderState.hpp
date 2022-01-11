#ifndef KMINTAPP_WANDERSTATE_HPP
#define KMINTAPP_WANDERSTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    template<typename Ty_>
    class WanderState : public State<Ty_>
    {
        private:
            kmint::delta_time _timePassed{};
            int _stepDuration;
            int _steps = 0;

        public:
            explicit WanderState(Ty_* data, int stepDuration = 1) : State<Ty_>(data), _stepDuration{stepDuration}
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;

                if (kmint::to_seconds(_timePassed) < _stepDuration) return;

                if (this->Data() != nullptr)
                {
                    auto edgeId = containers::Random::Next(0, static_cast<int>(this->Data()->node().num_edges()) - 1);
                    auto& edgeNode = this->Data()->node()[edgeId].to();

                    this->Data()->node(edgeNode);
                    ++_steps;
                }

                _timePassed = kmint::from_seconds(0);
            };

            void Enter() override;

            void Exit() override;

            [[nodiscard]] int Steps() const
            {
                return _steps;
            }
    };
}

#endif //KMINTAPP_WANDERSTATE_HPP
