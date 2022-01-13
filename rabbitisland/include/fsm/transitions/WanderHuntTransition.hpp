#ifndef KMINTAPP_WANDERHUNTTRANSITION_HPP
#define KMINTAPP_WANDERHUNTTRANSITION_HPP

#include "fsm/Transition.hpp"
#include "fsm/states/WanderState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class WanderHuntTransition : public Transition<Ty_>
    {
        private:
            int _steps;

        public:
            explicit WanderHuntTransition(std::weak_ptr<State<Ty_>> to, int steps = 10) : Transition<Ty_>(to),
                                                                                          _steps{steps}
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                auto wanderState = std::dynamic_pointer_cast<states::WanderState<Ty_>>(from);
                if (wanderState)
                {
                    return wanderState->Steps() >= _steps;
                }

                return false;
            }
    };
}

#endif //KMINTAPP_WANDERHUNTTRANSITION_HPP