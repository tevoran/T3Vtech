#include <te.h>

int main() {
	if(te_init("T3Vtech version 2 TEST WINDOW", 1366, 768, 0)!=TE_OKAY) {
		printf("error while initialization\n");
	}

	te_start_renderer(TE_SOFTWARE_RENDERER);

	//current tests
	te_color color;
	color.r=255;
	color.g=10;
	color.b=200;
	color.a=255;
	for(int i=200; i<600; i++)
	{
		for(int y=100; y<300; y++)
		{
			te_render(color, i, y);	
		}
	}
	te_update();

	SDL_Delay(3000);

	te_quit();
}