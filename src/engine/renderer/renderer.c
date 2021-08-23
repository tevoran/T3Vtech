#include <te.h>

#include <SDL2/SDL.h>

unsigned long te_current_renderer=TE_NO_RENDERER;
te_software_renderer *software_renderer=NULL;

int te_start_renderer(unsigned long FLAGS) {
	if(FLAGS & TE_SOFTWARE_RENDERER) {
		printf("Selecting the T3Vtech software renderer\n");
		te_current_renderer=TE_SOFTWARE_RENDERER;

		//starting the software rasterizer
		software_renderer=te_software_rasterizer_init();
	}
}

void te_render(te_vertex v1, te_vertex v2, te_vertex v3) {
	if(software_renderer!=NULL) {
		te_software_rasterizer_render_tri(v1, v2, v3);
	}
}


void te_update() {
	if(te_current_renderer==TE_SOFTWARE_RENDERER) {
		te_software_rasterizer_update();
	}
}


//cleaning up
void te_quit() {
	if(software_renderer!=NULL) {
		te_software_rasterizer_quit();
		free(software_renderer);
	}
}
