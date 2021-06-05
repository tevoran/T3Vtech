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

		uint32_t pixel_color=r;
		pixel_color=pixel_color<<8;
		pixel_color+=g;
		pixel_color=pixel_color<<8;
		pixel_color+=b;
		*pixel_ptr=pixel_color;
	}
}

void t3v::software_rasterizer::draw_pixel_fast(
	uint32_t* pixel_ptr,
	const uint8_t r, 
	const uint8_t g, 
	const uint8_t b)
{
	uint32_t pixel_color=r;
	pixel_color=pixel_color<<8;
	pixel_color+=g;
	pixel_color=pixel_color<<8;
	pixel_color+=b;
	*pixel_ptr=pixel_color;
}

void t3v::software_rasterizer::draw_pixel_fast_simple(
	uint32_t* pixel_ptr,
	const t3v::color color)
{
	*pixel_ptr=*(uint32_t*)&color;
}

void t3v::software_rasterizer::draw_pixel_fast_64(
	uint64_t* pixel_ptr,
	const uint8_t r, 
	const uint8_t g, 
	const uint8_t b,
	const uint8_t r2, 
	const uint8_t g2, 
	const uint8_t b2)
{
	uint64_t pixel_color=r;
	pixel_color=pixel_color<<8;
	pixel_color+=g;
	pixel_color=pixel_color<<8;
	pixel_color+=b;
	pixel_color=pixel_color<<8;
	pixel_color+=r2;
	pixel_color=pixel_color<<8;
	pixel_color+=g2;
	pixel_color=pixel_color<<8;
	pixel_color+=b2;
	*pixel_ptr=pixel_color;
}