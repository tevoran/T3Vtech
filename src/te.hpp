#pragma once

//vendor
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//stdlib
#include <iostream>
#include <cstring>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <chrono>
#include <cmath>
#include <string>
#include <algorithm>
#include <limits>


//engine headers
#include <definitions.hpp>
#include <engine/multithreading.hpp>
#include <engine/renderer/renderer_data_types.hpp>
#include <engine/math/math.hpp>
#include <engine/assets/assets.hpp>
#include <engine/renderer/renderer.hpp>
#include <engine/objects/2d/object2d.hpp>
#include <engine/renderer/software_rasterizer/software_rasterizer.hpp>
#include <engine/general.hpp>
#include <engine/objects/3d/object3d.hpp>

#ifdef __MINGW32__
	#undef main
#endif