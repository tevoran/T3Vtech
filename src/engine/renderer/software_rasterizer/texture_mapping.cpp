#include <te.hpp>

t3v::color t3v::software_rasterizer::texture_mapping(float u, float v, t3v::texture *texture)
{
	t3v::color pixel_color;

	//using only the fraction part so textures can be repeated
	u=u-(int)u;
	v=v-(int)v;

	//texture mapping
	int u_int=u*(float)texture->w;
	int v_int=v*(float)texture->h;
	int offset=(u_int+v_int*texture->w)*TE_COLORDEPTH; //colordepth is 4 bytes

	pixel_color.r=texture->data[offset];
	offset++;
	pixel_color.g=texture->data[offset];
	offset++;
	pixel_color.b=texture->data[offset];
	offset++;
	pixel_color.a=255;

	return pixel_color;
}