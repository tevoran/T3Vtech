#include <general/general.h>

#include <SDL2/SDL.h>
#include <stdio.h>

extern SDL_Window *window;

int te_init(const char *window_title, int resx, int resy)
{
	printf("Welcome to T3Vtech engine version 2\n");

	printf("Initializing SDL2...");
	if(SDL_Init(
		SDL_INIT_TIMER|
		SDL_INIT_AUDIO|
		SDL_INIT_VIDEO|
		SDL_INIT_EVENTS)==0)
	{
		printf("done\n");
	}
	else
	{
		printf("error\n");

	}

	printf("Creating Window...");
	window=SDL_CreateWindow(
		window_title, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		resx,
		resy,
		0);

	if(window==NULL)
	{
		printf("error\n");
	}
	else
	{
		printf("done\n");
	}

	SDL_Delay(3000);
	return 0;
}