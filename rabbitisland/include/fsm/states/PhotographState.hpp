#ifndef KMINT_ASSESSMENT_PHOTOGRAPHSTATE_HPP
#define KMINT_ASSESSMENT_PHOTOGRAPHSTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    template<typename Ty_>
    class PhotographState : public State<Ty_>
    {
        private:
            kmint::delta_time _timePassed{};
            kmint::delta_time _totalDuration{};
            std::function<double(const Ty_*)> _waitDuration;

        public:
            explicit PhotographState(Ty_* data, double waitDuration) : State<Ty_>(data), _waitDuration{[waitDuration](const Ty_*) {return waitDuration;}}
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _timePassed += deltaTime;
                _totalDuration += deltaTime;

                if (kmint::to_seconds(_timePassed) < WaitDuration()) return;

                _timePassed = kmint::from_seconds(0);
            };

            double WaitDuration()
            {
                return _waitDuration(this->Data());
            }

            kmint::delta_time Duration()
            {
                return _totalDuration;
            }

            void Enter() override;

            void Exit() override;
    };
}


#endif //KMINT_ASSESSMENT_PHOTOGRAPHSTATE_HPP
