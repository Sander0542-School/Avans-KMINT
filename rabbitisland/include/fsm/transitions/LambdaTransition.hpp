#ifndef KMINT_ASSESSMENT_LAMBDATRANSITION_HPP
#define KMINT_ASSESSMENT_LAMBDATRANSITION_HPP

#include "fsm/Transition.hpp"
#include "fsm/State.hpp"

#include <functional>

namespace fsm::transitions
{
    template<typename Ty_>
    class LambdaTransition : public Transition<Ty_>
    {
        private:
            std::function<double(const std::shared_ptr<State<Ty_>>&)> _lambda;

        public:
            LambdaTransition(std::weak_ptr<State<Ty_>> to, std::function<bool(const std::shared_ptr<State<Ty_>>&)> lambda) : Transition<Ty_>(to),
                                                                                                                      _lambda{lambda}
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                return _lambda(from);
            }
    };
}

#endif //KMINT_ASSESSMENT_LAMBDATRANSITION_HPP
