#ifndef KMINT_ASSESSMENT_WANDERSTATE_HPP
#define KMINT_ASSESSMENT_WANDERSTATE_HPP

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
            kmint::delta_time _totalDuration{};
            int _steps = 0;

        public:
            explicit WanderState(Ty_* data) : State<Ty_>(data)
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
                    HandleStep();
                }

                _timePassed = kmint::from_seconds(0);
            };

            [[nodiscard]] double StepDuration() const;

            kmint::delta_time Duration()
            {
                return _totalDuration;
            }
			
            void Enter()
            {
                _timePassed = kmint::from_seconds(0);
                _totalDuration = kmint::from_seconds(0);
                _steps = 0;

                AfterEnter();
            }
			
            void Exit() override;

            virtual void AfterEnter();

            void HandleStep();

            [[nodiscard]] int Steps() const
            {
                return _steps;
            }
    };
}

#endif //KMINT_ASSESSMENT_WANDERSTATE_HPP
