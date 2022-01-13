#ifndef KMINT_ASSESSMENT_PROBABLISTICTRANSITION_HPP
#define KMINT_ASSESSMENT_PROBABLISTICTRANSITION_HPP

#include "fsm/Transition.hpp"
#include <functional>

namespace fsm::states
{
    using ChanceFunction = std::function<double()>;

    template<typename Ty_>
    class ProbablisticTransition : public Transition<Ty_>
    {
        private:
            const double& _randomValue;
            double& _currentValue;
            ChanceFunction _changeFunction;

        public:
            ProbablisticTransition(std::weak_ptr<State<Ty_>> to, double& currentValue, const double& randomValue, const ChanceFunction& chanceFunction) : Transition<Ty_>(to), _currentValue(currentValue), _randomValue(randomValue), _changeFunction{changeFunction}
            {
            }

            bool Condition(std::shared_ptr<State<Ty_>> from) const override
            {
                _currentValue += _changeFunction();
                return _currentValue >= _randomValue;
            }
    };
}

#endif //KMINT_ASSESSMENT_PROBABLISTICTRANSITION_HPP
