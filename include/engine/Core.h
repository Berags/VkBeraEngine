//
// Created by Jacopo Beragnoli on 04/05/22.
//
// This header file is used to include all necessary headers from the Engine
//

#ifndef MINIMINIMOTORWAYS_CORE_H
#define MINIMINIMOTORWAYS_CORE_H

#include "Buffer.h"
#include "Camera.h"
#include "Descriptors.h"
#include "Device.h"
#include "FrameInfo.h"
#include "GameObject.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "Pipeline.h"
#include "Renderer.h"
#include "SwapChain.h"
#include "Utils.h"
#include "Window.h"

#include "exceptions/Exception.h"

#include "ecs/IComponent.h"
#include "ecs/TestComponent.h"
#include "ecs/Entity.h"
#include "ecs/EntityManager.h"

#include "systems/RenderSystem.h"
#include "systems/PointLightSystem.h"

#endif //MINIMINIMOTORWAYS_CORE_H
