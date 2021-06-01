#pragma once

//vendor
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

//stdlib
#include <iostream>
#include <cstring>
#include <thread>
#include <vector>
#include <condition_variable>
#include <barrier>

//engine headers
#include <definitions.hpp>
#include <engine/renderer/renderer.hpp>
#include <engine/renderer/software_rasterizer/software_rasterizer.hpp>
#include <engine/general.hpp>