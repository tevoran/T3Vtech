#include <te.hpp>

void t3v::software_rasterizer::draw_pixel_basic(
	const int x, 
	const int y, 
	const uint8_t r, 
	const uint8_t g, 
	const uint8_t b)
{
	if(x>=0 && x<m_resx && y>=0 && y<m_resy)
	{
		uint32_t *pixel_ptr=(uint32_t*)m_window_surface->pixels;
		pixel_ptr=pixel_ptr+x+y*m_resx;

		register uint32_t pixel_color=r;
		pixel_color=pixel_color<<8;
		pixel_color+=g;
		pixel_color=pixel_color<<8;
		pixel_color+=b;
		*pixel_ptr=pixel_color;
	}
}