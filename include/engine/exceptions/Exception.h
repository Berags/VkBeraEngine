//
// Created by Jacopo Beragnoli on 02/04/22.
//

#ifndef MINIMINIMOTORWAYS_EXCEPTION_H
#define MINIMINIMOTORWAYS_EXCEPTION_H

#include <exception>

#include "file/UnableToOpenFileException.h"

#include "vulkan/FailedToCreatePipeLineLayoutException.h"
#include "vulkan/FailedToCreateRenderPassException.h"
#include "vulkan/FailedToCreateShaderModuleException.h"
#include "vulkan/FailedToCreateSwapChainException.h"
#include "vulkan/FailedToCreateSynchronizationObjectException.h"
#include "vulkan/FailedToCreateTextureImageViewException.h"
#include "vulkan/FailedToFindVulkanSupportedGPUException.h"
#include "vulkan/FailedToSubmitDrawCommandBufferException.h"

#include "window/FailedToCreateWindowSurfaceException.h"
#include "window/UnableToInitGLFWException.h"
#include "window/UnableToStartWindowException.h"

#endif //MINIMINIMOTORWAYS_EXCEPTION_H
