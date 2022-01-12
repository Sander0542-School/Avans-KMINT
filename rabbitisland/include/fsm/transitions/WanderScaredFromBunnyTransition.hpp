#ifndef KMINT_ASSESSMENT_WanderScaredFromBunnyTransition_HPP
#define KMINT_ASSESSMENT_WanderScaredFromBunnyTransition_HPP

#include "kmint/primitives.hpp"

#include "fsm/Transition.hpp"
#include "fsm/states/WanderState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class WanderScaredFromBunnyTransition : public Transition<Ty_>
    {
        public:
            explicit WanderScaredFromBunnyTransition(std::weak_ptr<State<Ty_>> to) : Transition<Ty_>(to)
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto wanderState = std::dynamic_pointer_cast<states::WanderState<Ty_>>(from);
                if (wanderState)
                {
                    return wanderState->Data()->IsRabbitNearby();
                }

                return false;
            }
    };
}

#endif //KMINT_ASSESSMENT_WanderScaredFromBunnyTransition_HPP
