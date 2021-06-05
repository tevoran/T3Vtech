#pragma once

//vendor
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

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
#include <engine/math/math.hpp>
#include <engine/renderer/vertex.hpp>
#include <engine/renderer/renderer.hpp>
#include <engine/renderer/software_rasterizer/software_rasterizer.hpp>
#include <engine/general.hpp>