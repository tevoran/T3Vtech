#pragma once

//vendor
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

//stdlib
#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <barrier>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <limits>

//engine headers
#include <definitions.hpp>
#include <engine/renderer/renderer_data_types.hpp>
#include <engine/math/math.hpp>
#include <engine/assets/assets.hpp>
#include <engine/renderer/renderer.hpp>
#include <engine/renderer/software_rasterizer/software_rasterizer.hpp>
#include <engine/general.hpp>
#include <engine/renderer/object3d.hpp>