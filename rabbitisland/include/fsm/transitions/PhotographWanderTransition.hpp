#ifndef KMINT_ASSESSMENT_PHOTOGRAPHWANDERTRANSITION_HPP
#define KMINT_ASSESSMENT_PHOTOGRAPHWANDERTRANSITION_HPP

#include "kmint/primitives.hpp"

#include "fsm/Transition.hpp"
#include "fsm/states/FreezeState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class PhotographWanderTransition : public Transition<Ty_>
    {
        private:
            double _duration;

        public:
            explicit PhotographWanderTransition(std::weak_ptr<State<Ty_>> to, double duration = 3) : Transition<Ty_>(to),
                                                                                                _duration{duration}
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto photographState = std::dynamic_pointer_cast<states::FreezeState<Ty_>>(from);
                if (photographState)
                {
                    return kmint::to_seconds(photographState->Duration()) >= _duration;
                }

                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_PHOTOGRAPHWANDERTRANSITION_HPP
