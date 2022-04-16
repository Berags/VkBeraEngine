//
// Created by Jacopo Beragnoli on 16/04/22.
//

#ifndef MINIMINIMOTORWAYS_UTILS_H
#define MINIMINIMOTORWAYS_UTILS_H

#include <functional>

namespace Engine {
    template<typename T, typename... Rest>
    void hashCombine(std::size_t &seed, const T &v, const Rest &... rest) {
        seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    };
}


#endif //MINIMINIMOTORWAYS_UTILS_H
