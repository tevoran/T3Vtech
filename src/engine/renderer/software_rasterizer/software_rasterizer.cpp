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
	std::cout << "HELL YEAH!" << std::endl;
}

void t3v::software_rasterizer::update()
{
	SDL_UpdateWindowSurface(m_window);
	memset(m_window_surface->pixels, 200, m_resx*m_resy*sizeof(uint32_t));
}