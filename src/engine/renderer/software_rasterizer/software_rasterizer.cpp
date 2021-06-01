#include <te.hpp>

t3v::software_rasterizer::software_rasterizer(SDL_Window *window)
{
	m_window=window;
	m_window_surface=SDL_GetWindowSurface(window);
	if(m_window_surface==NULL)
	{
		std::cout << "[ERROR] software rasterizer can't get the window surface to draw on" << std::endl;
		exit(0);
	}

	m_resx=m_window_surface->w;
	m_resy=m_window_surface->h;

	m_num_cpu_threads=std::thread::hardware_concurrency();
}

void t3v::software_rasterizer::render()
{
	for(int ix=100; ix<2000; ix++)
	{
		for(int iy=100; iy<2000; iy++)
		{
			draw_pixel_basic(ix,iy,0,0,200);
		}
	}
}

void t3v::software_rasterizer::update()
{
	if(SDL_UpdateWindowSurface(m_window)!=0)
	{
		std::cout << "[ERROR] Couldn't update window surface anymore" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black
}