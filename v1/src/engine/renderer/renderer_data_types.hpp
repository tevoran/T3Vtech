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


	//texture
	struct texture
	{
		int w;
		int h;
		uint8_t *data=NULL;
	};
	
	//texture coordinates for a vertex
	struct tex
	{
		float u;
		float v;
	};

	struct vertex
	{
		glm::vec4 pos={0,0,0,1};
		t3v::color color;
		t3v::tex tex; //texture uv-coordinates
		t3v::texture *texture=NULL; //a pointer to the used texture and gets set by the renderer
	};
}