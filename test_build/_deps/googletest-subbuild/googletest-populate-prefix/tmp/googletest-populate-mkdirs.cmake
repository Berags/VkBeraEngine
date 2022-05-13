# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-src"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-build"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix/src"
        "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
        )

set(configSubDirs)
foreach (subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jacopo/CLionProjects/MiniminiMotorways/test_build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach ()
