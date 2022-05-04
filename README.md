# VkBeraEngine

Game Engine built with just C++ and Vulkan API.

[![CodeFactor](https://www.codefactor.io/repository/github/berags/vkberaengine/badge)](https://www.codefactor.io/repository/github/berags/vkberaengine)

## Dev Environment

This engine uses the following libraries:
- Vulkan SDK
- GLFW
- GLM (Often included with Vulkan SDK)

You can follow the setup steps <a href="https://vulkan-tutorial.com/Development_environment">here</a>. 

The following libraries are included as headers:
- <a href="https://github.com/nothings/stb">stb_image</a>
- <a href="https://github.com/nlohmann/json">json</a>
- <a href="https://github.com/tinyobjloader/tinyobjloader">tiny_obj_loader</a>
- <a href="https://github.com/ocornut/imgui">ImGui</a>

## Build and Run
### MacOS/Unix Operating Systems
Just run the `build.sh` script or the following bash commands:
```bash
mkdir -p build
cd build || exit
cmake -S ../ -B .
make && make Shaders && ./MiniminiMotorways
cd ..
```
### Windows 
#### Using Visual Studio
In windows powershell

```
 cd MiniminiMotorways 
 mkdir build
 cmake -S . -B .\build\
```

If cmake finished successfully, it will create a MiniminiMotorways.sln file in the build directory that can be opened with visual studio. In visual studio right click the Shaders project -> build, to build the shaders. Right click the project -> set as startup project. Change from debug to release, and then build and start without debugging.

#### Using MinGW
Change the value of `envWindowsExample.cmake` to match your development settings (i.e. set Vulkan SDK Path, GLM Path and GLFW Path).
Run `build.bat` or the following Batch commands:
```bat
if not exist build mkdir build
copy envWindowsExample.cmake .env.cmake
cd build
cmake -S ../ -B . -G "MinGW Makefiles"
mingw32-make.exe && mingw32-make.exe Shaders
cd ..
```