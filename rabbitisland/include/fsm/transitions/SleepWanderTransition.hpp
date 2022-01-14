#ifndef KMINT_ASSESSMENT_SLEEPWANDERTRANSITION_HPP
#define KMINT_ASSESSMENT_SLEEPWANDERTRANSITION_HPP

#include "fsm/Transition.hpp"
#include "fsm/states/FreezeState.hpp"

#include "consts.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class SleepWanderTransition : public Transition<Ty_>
    {
        public:
            SleepWanderTransition(std::weak_ptr<State<Ty_>> to) : Transition<Ty_>(to)
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto freezeState = std::dynamic_pointer_cast<states::FreezeState<Ty_>>(from);

                if (freezeState)
                {
                    if (kmint::to_seconds(freezeState->Duration()) >= DogSleepTime * Period)
                    {
                        return true;
                    }
                }

                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_SLEEPWANDERTRANSITION_HPP
