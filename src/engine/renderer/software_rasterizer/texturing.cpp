#include <te.hpp>

t3v::color t3v::software_rasterizer::texture_mapping(float u, float v)
{
	t3v::color pixel_color;

	//test texture
	uint8_t texture[16]={30,30,30,0, 0,150,0,0, 0,150,0,0, 30,30,30,0};
	int w=2;
	int h=2;
	int color_depth=4;

	u=u-(int)u;
	v=v-(int)v;

	//texture mapping
	int u_int=u*(float)w;
	int v_int=v*(float)h;
	int offset=(u_int+v_int*w)*color_depth;

	pixel_color.r=texture[offset];
	offset++;
	pixel_color.g=texture[offset];
	offset++;
	pixel_color.b=texture[offset];

	return pixel_color;
}
