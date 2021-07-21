#include <te.h>

unsigned long current_renderer=TE_NO_RENDERER;

int te_start_renderer(unsigned long FLAGS)
{
	if(FLAGS & TE_SOFTWARE_RENDERER)
	{
		printf("Selecting the T3Vtech software renderer\n");
		current_renderer=TE_SOFTWARE_RENDERER;

		//starting the software rasterizer
		te_software_rasterizer_init();
	}
}
