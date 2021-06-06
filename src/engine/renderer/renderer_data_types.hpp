#pragma once
#include <te.hpp>

namespace t3v
{
	struct color
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t a;
	};

	struct texture
	{
		int w;
		int h;
		uint8_t *data=NULL;
	};


	//vertex
	struct tex
	{
		float u;
		float v;
	};

	struct vertex
	{
		glm::vec3 pos;
		t3v::color color;
		t3v::tex tex;
	};
}