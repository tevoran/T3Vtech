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
		int w=2;
		int h=2;
		t3v::color data[4]=
		{
			{30,30,30,0}, {0,0,150,0},
			{0,0,150,0}, {30,30,30,0}
		};
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