#ifndef KMINTAPP_WANDERSTATE_HPP
#define KMINTAPP_WANDERSTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"
#include "consts.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    template<typename Ty_>
    class WanderState : public State<Ty_>
    {
        private:
            kmint::delta_time _timePassed{};
            int _steps = 0;

        public:
            explicit WanderState(Ty_* data) : State<Ty_>(data)
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;

                if (kmint::to_seconds(_timePassed) < StepDuration()) return;

                if (this->Data() != nullptr)
                {
                    auto edgeId = containers::Random::Next(0, static_cast<int>(this->Data()->node().num_edges()) - 1);
                    auto& edgeNode = this->Data()->node()[edgeId].to();

                    this->Data()->node(edgeNode);
                    ++_steps;
                }

                _timePassed = kmint::from_seconds(0);
            };

            [[nodiscard]] double StepDuration() const;

            void Enter() override;

            void Exit() override;

            [[nodiscard]] int Steps() const
            {
                return _steps;
            }
    };
}

#endif //KMINTAPP_WANDERSTATE_HPP
