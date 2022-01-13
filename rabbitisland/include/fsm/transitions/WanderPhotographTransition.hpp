#ifndef KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP
#define KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP

#include "kmint/primitives.hpp"

#include "fsm/Transition.hpp"
#include "fsm/states/WanderState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class WanderPhotographTransition : public Transition<Ty_>
    {
        private:
            double _duration;

        public:
            explicit WanderPhotographTransition(std::weak_ptr<State<Ty_>> to, double duration = 10) : Transition<Ty_>(to),
                                                                                                _duration{duration}
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto wanderState = std::dynamic_pointer_cast<states::WanderState<Ty_>>(from);
                if (wanderState)
                {
                    return kmint::to_seconds(wanderState->Duration()) >= _duration;
                }

                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP
