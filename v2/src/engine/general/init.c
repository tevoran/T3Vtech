#include <te.h>
#include <general/general.h>

#include <SDL2/SDL.h>
#include <stdio.h>

int te_init()
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
	SDL_Delay(3000);
	return 0;
}