#ifndef KMINT_ASSESSMENT_FREEZESTATE_HPP
#define KMINT_ASSESSMENT_FREEZESTATE_HPP

#include "containers/Random.hpp"
#include "fsm/State.hpp"

#include "kmint/play.hpp"

namespace fsm::states
{
    template<typename Ty_>
    class FreezeState : public State<Ty_>
    {
        private:
            kmint::delta_time _totalDuration{};

        public:
            explicit FreezeState(Ty_* data) : State<Ty_>(data)
            {
            }

            void Tick(kmint::delta_time deltaTime) override
            {
                _totalDuration += deltaTime;
            };

            kmint::delta_time Duration()
            {
                return _totalDuration;
            }

            void Enter() override
            {
                _totalDuration = kmint::from_seconds(0);
            }

            void Exit() override
            {
            }
    };
}


#endif //KMINT_ASSESSMENT_FREEZESTATE_HPP
