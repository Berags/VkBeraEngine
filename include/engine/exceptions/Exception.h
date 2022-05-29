//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef VKBERAENGINE_EXCEPTION_H
#define VKBERAENGINE_EXCEPTION_H

#include <exception>
#include <cstdio>
#include <iostream>

namespace Engine::Exceptions {
#define PRINT_STACK_TRACE std::cerr << "Generated from file: " << __FILE__ << "\nFunction call: " << __func__ << "\nLine: " << __LINE__<< "\n";
}

#include "file/UnableToOpenFileException.h"

#include "vulkan/FailedToCreateVkObject.h"
#include "vulkan/FailedToFindVulkanSupportedGPUException.h"
#include "vulkan/FailedToSubmitDrawCommandBufferException.h"

#include "window/FailedToCreateWindowSurfaceException.h"
#include "window/UnableToInitGLFWException.h"
#include "window/UnableToStartWindowException.h"

#endif //VKBERAENGINE_EXCEPTION_H
