#include <te.h>
#include <math.h>

#define FRAMES 2000

int main() {
	if(te_init("T3Vtech version 2 TEST WINDOW", 1366, 768, 0)!=TE_OKAY) {
		printf("error while initialization\n");
	}

	te_start_renderer(TE_SOFTWARE_RENDERER);

	//current tests
	te_vertex v1;
	v1.x=0.1;
	v1.y=0.1;
	v1.z=0.1;
	v1.color.r=250;
	v1.color.g=200;
	v1.color.b=0;
	v1.color.a=255;

	te_vertex v2;
	v2.x=0.1;
	v2.y=0.3;
	v2.z=0.1;
	v2.color.r=255;
	v2.color.g=255;
	v2.color.b=255;
	v2.color.a=255;

	te_vertex v3;
	v3.x=0.8;
	v3.y=0.7;
	v3.z=0.1;
	v3.color.r=255;
	v3.color.g=255;
	v3.color.b=255;
	v3.color.a=255;

	te_vertex v0;
	v0.x=0.5;
	v0.y=0.2;
	v0.z=0.1;
	v0.color.r=255;
	v0.color.g=255;
	v0.color.b=0;
	v0.color.a=255;

	unsigned long t1= SDL_GetTicks();

	for(int i=0; i<FRAMES;i++)
	{
		v1.x=0.5*sin((float)i/2000)+0.5;
		te_render(v1, v2, v3);
		//te_render(v0, v2, v3);
		te_update();
	}
	unsigned long t2= SDL_GetTicks();
	unsigned long dt=t2-t1;

	printf("%f ms per frame\n", ((float)dt/FRAMES));
	printf("equals %f FPS on average\n", 1000/((float)dt/FRAMES));

	te_quit();
}