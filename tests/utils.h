//
// Created by Jacopo Beragnoli on 14/05/22.
//

#ifndef VKBERAENGINE_TESTUTILS_H
#define VKBERAENGINE_TESTUTILS_H

namespace Tests::Utils {
    template<typename T, typename ... Ts>
    void throwException(Ts &... args) {
        throw T(args...);
    }
}

#endif //VKBERAENGINE_UTILS_H
