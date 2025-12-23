#pragma once

#include "../main.hpp"

namespace utils {
    template <typename T> T randomNumber(T min, T max, std::vector<T> excluding = {}) {
        std::random_device rd;
        std::mt19937_64 mt(rd());

        if constexpr (std::is_integral<T>::value) {
            std::uniform_int_distribution<T> dist(min, max);
            T number = dist(mt);
            for (int i = 0; i < excluding.size(); ++i)
                if (excluding[i] == number) {
                    number = dist(mt);
                    i = 0;
                }
            return number;
        }
        else if constexpr (std::is_floating_point<T>::value) {
            std::uniform_real_distribution<T> dist(min, max);
            T number = dist(mt);
            for (int i = 0; i < excluding.size(); ++i)
                if (excluding[i] == number) {
                    number = dist(mt);
                    i = 0;
                }
            return number;
        }
        else {
            printf("[UTILS][randomNumber]: Number type unsupported!\n");
            return T{};
        }
    }
}