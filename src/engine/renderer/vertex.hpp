#pragma once
#include <te.hpp>

namespace t3v
{
	struct color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};

	struct vertex
	{
		glm::vec3 pos;
		t3v::color color;
	};
}