if not exist build mkdir build
copy envWindowsExample.cmake .env.cmake
cd build
cmake -S ../ -B . -G "MinGW Makefiles"
mingw32-make.exe && mingw32-make.exe Shaders
cd ..