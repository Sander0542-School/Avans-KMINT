#ifndef KMINT_ASSESSMENT_RANDOM_HPP
#define KMINT_ASSESSMENT_RANDOM_HPP

#include <random>

namespace containers
{
    class Random
    {
        private:
            static Random _instance;
            std::default_random_engine _engine;

            Random()
            {
                std::random_device device{};
                _engine = std::default_random_engine{device()};
            }

        public:
            static int Next(int min, int max)
            {
                std::uniform_int_distribution<int> dist{min, max};
                return dist(_instance._engine);
            }

            Random(const Random&) = delete;

            Random& operator=(const Random&) = delete;

            Random(const Random&&) = delete;

            Random& operator=(Random&&) = delete;
    };
}

#endif //KMINT_ASSESSMENT_RANDOM_HPP
