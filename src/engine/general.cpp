#include <engine/general.hpp>

#include <te.hpp>


//engine initialization
t3v::engine::engine()
{
	std::cout << "Initializing T3V-engine" << std::endl;

	//getting SDL2 working
	std::cout << "Initializing SDL2...";
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
		std::cout << "[ERROR] SDL2 couldn't be initialized" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}

	m_window=SDL_CreateWindow("T3V-ENGINE test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_resx, m_resy, SDL_WINDOW_FULLSCREEN);
	if(m_window==NULL)
	{
		std::cout << "[ERROR] SDL2 couldn't create a window" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}
	std::cout << "done" << std::endl;

	std::cout << "Using resolution " << m_resx << "x" << m_resy << std::endl;

	std::cout << "T3V-engine successfully initialized" << std::endl;

}

t3v::engine::~engine()
{
	SDL_Quit();
}

void t3v::engine::choose_renderer(int renderer_type)
{
	m_renderer_type=renderer_type;

	//creating the right renderer
	switch(renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer = new t3v::software_rasterizer(m_window);
			break;
	}
}

void t3v::engine::render()
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_NO_RENDERER:
			m_renderer.render();
			break;

		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->render();
			break;
	}
}

void t3v::engine::update()
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->update();
			break;

		default:
			m_renderer.update();
			break;		
	}
}