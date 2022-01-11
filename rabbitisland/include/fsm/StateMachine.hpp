#ifndef KMINTAPP_STATEMACHINE_HPP
#define KMINTAPP_STATEMACHINE_HPP

#include "State.hpp"
#include "Transition.hpp"

#include <vector>

namespace fsm
{
    template<typename Ty_>
    class StateMachine
    {
        private:
            std::vector<std::shared_ptr<State<Ty_>>> _states{};
            std::weak_ptr<State<Ty_>> _currentState{};

        public:
            void StateTick(kmint::delta_time deltaTime)
            {
                if (_currentState.expired())
                {
                    if (_states.empty()) return;

                    _currentState = {_states[0]};
                    _currentState.lock()->Enter();
                }

                auto currentState = _currentState.lock();
                currentState->Tick(deltaTime);

                for (const std::shared_ptr<Transition<Ty_>>& transition: currentState->Transitions())
                {
                    if (transition->Condition(currentState))
                    {
                        currentState->Exit();
                        _currentState = transition->To();
                        _currentState.lock()->Enter();
                        break;
                    }
                }
            }

            void AddState(std::shared_ptr<State<Ty_>> state)
            {
                _states.push_back(state);
            }
    };
}

#endif //KMINTAPP_STATEMACHINE_HPP
