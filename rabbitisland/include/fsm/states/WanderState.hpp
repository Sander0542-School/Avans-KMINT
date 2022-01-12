#ifndef KMINT_ASSESSMENT_WANDERSTATE_HPP
#define KMINT_ASSESSMENT_WANDERSTATE_HPP

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
            kmint::delta_time _totalDuration{};
            std::function<double(const Ty_*)> _stepDuration;
            int _steps = 0;

        public:
            explicit WanderState(Ty_* data, std::function<double(const Ty_*)> stepDuration) : State<Ty_>(data),
                                                                                              _stepDuration{stepDuration}
            {
            }

            explicit WanderState(Ty_* data, double stepDuration) : WanderState(data, [stepDuration](const Ty_*) {return stepDuration;})
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;
                _totalDuration += deltaTime;

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

            double StepDuration()
            {
                return _stepDuration(this->Data());
            }

            kmint::delta_time Duration()
            {
                return _totalDuration;
            }

            void Enter() override;

            void Exit() override;

            [[nodiscard]] int Steps() const
            {
                return _steps;
            }
    };
}

#endif //KMINT_ASSESSMENT_WANDERSTATE_HPP
