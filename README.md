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
Work in progress.
