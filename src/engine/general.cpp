#include <engine/general.hpp>

#include <te.hpp>

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

	window=SDL_CreateWindow("T3V-ENGINE test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_FULLSCREEN);
	if(window==NULL)
	{
		std::cout << "[ERROR] SDL2 couldn't create a window" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}
	std::cout << "done" << std::endl;

	std::cout << "T3V-engine successfully initialized" << std::endl;

}

t3v::engine::~engine()
{

}