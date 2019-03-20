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

//SDL
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>

//OpenGL
#include <gl/GL.h>

//Vulkan
#include <vulkan/vulkan.hpp>

//Element
#include "../logging/Logger.h"
#include "util/macro.h"

#include <imgui.h>
#include <spdlog/spdlog.h>