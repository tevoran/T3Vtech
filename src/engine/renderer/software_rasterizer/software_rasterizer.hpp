#pragma once
#include <te.hpp>


namespace t3v
{
	class software_rasterizer : public t3v::renderer
	{
	private:
		SDL_Surface *m_window_surface=NULL;
		SDL_Window *m_window=NULL;
		
		int m_num_cpu_threads=0;

		void draw_pixel_basic(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b);

	public:
		software_rasterizer(SDL_Window *window);
		void render();
		void update();
	};
}