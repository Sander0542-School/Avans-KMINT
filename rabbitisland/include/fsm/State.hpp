#ifndef KMINT_ASSESSMENT_STATE_HPP
#define KMINT_ASSESSMENT_STATE_HPP

#include "Transition.hpp"

#include "kmint/primitives.hpp"

#include <vector>

namespace fsm
{
    template<typename Ty_>
    class State
    {
        private:
            std::vector<std::shared_ptr<Transition<Ty_>>> _transitions{};
            Ty_* _data;

        public:
            explicit State(Ty_* data) : _data{data}
            {
            }

            virtual void Enter() = 0;

            virtual void Tick(kmint::delta_time deltaTime) = 0;

            virtual void Exit() = 0;

            void AddTransition(std::shared_ptr<Transition<Ty_>> transition)
            {
                _transitions.push_back(transition);
            }

            const std::vector<std::shared_ptr<Transition<Ty_>>>& Transitions() const
            {
                return _transitions;
            }

            Ty_* Data() const
            {
                return _data;
            }
    };
}

#endif //KMINT_ASSESSMENT_STATE_HPP
