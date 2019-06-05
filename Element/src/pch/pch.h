#pragma once

//STL
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <memory>
#include <random>

//third party
#include <spdlog/spdlog.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>

#include <gl/GL.h>
#include <vulkan/vulkan.hpp>
#include <imgui/imgui.h>
#include <glm/glm.hpp>

//Element
#include "../logging/Logger.h"
#include "../util/macro.h"
#include "../core/platform/Platform.h"