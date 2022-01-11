#ifndef KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP
#define KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP

#include "fsm/Transition.hpp"
#include "fsm/states/WanderState.hpp"

namespace fsm::transitions
{
    template<typename Ty_>
    class WanderPhotographTransition : public Transition<Ty_>
    {
        private:
            int _steps;

        public:
            explicit WanderPhotographTransition(std::weak_ptr<State<Ty_>> to, int steps = 10) : Transition<Ty_>(to),
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

#endif //KMINT_ASSESSMENT_WANDERPHOTOGRAPHTRANSITION_HPP
