//
// Created by Jacopo Beragnoli on 14/05/22.
//

#ifndef MINIMINIMOTORWAYS_TESTUTILS_H
#define MINIMINIMOTORWAYS_TESTUTILS_H

namespace Tests::Utils {
    template<typename T, typename ... Ts>
    void throwException(Ts &... args) {
        throw T(args...);
    }
}

#endif //MINIMINIMOTORWAYS_UTILS_H
