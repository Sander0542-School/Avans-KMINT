#ifndef KMINT_ASSESSMENT_ScaredFromBunnyWanderTransition_HPP
#define KMINT_ASSESSMENT_ScaredFromBunnyWanderTransition_HPP

#include "kmint/primitives.hpp"

#include "fsm/Transition.hpp"
#include "fsm/states/FreezeState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class ScaredFromBunnyWanderTransition : public Transition<Ty_>
    {
        public:
            explicit ScaredFromBunnyWanderTransition(std::weak_ptr<State<Ty_>> to) : Transition<Ty_>(to)
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto freezeState = std::dynamic_pointer_cast<states::FreezeState<Ty_>>(from);
                if (freezeState)
                {
                    return !freezeState->Data()->IsRabbitNearby();
                }

                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_ScaredFromBunnyWanderTransition_HPP
