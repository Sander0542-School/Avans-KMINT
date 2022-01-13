#ifndef KMINT_ASSESSMENT_TRANSITION_HPP
#define KMINT_ASSESSMENT_TRANSITION_HPP

#include <memory>

namespace fsm
{
    template<typename Ty_>
    class State;

    template<typename Ty_>
    class Transition
    {
        private:
            std::weak_ptr<State<Ty_>> _to;

        public:
            explicit Transition(std::weak_ptr<State<Ty_>> to) : _to{to}
            {
            }

            [[nodiscard]] virtual bool Condition(std::shared_ptr<State<Ty_>> from) const = 0;

            const std::weak_ptr<State<Ty_>>& To() const
            {
                return _to;
            }
    };
}

#endif //KMINT_ASSESSMENT_TRANSITION_HPP
