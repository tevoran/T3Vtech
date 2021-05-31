#pragma once
#include <te.hpp>


namespace t3v
{
	class software_rasterizer : t3v::renderer
	{
	private:
		SDL_Surface *m_window_surface=NULL;

		int m_num_cpu_threads=0;

	public:
		software_rasterizer(SDL_Window *window);
		void render();
	};
}