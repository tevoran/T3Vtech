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

void te_render(te_color pixel_color, int x, int y) {
	SDL_Color *pixel_ptr=software_renderer->window_surface->pixels;
	pixel_ptr+=y*software_renderer->resx + x;
	te_software_rasterizer_draw_pixel( 
		pixel_ptr,
		&pixel_color);
}


void te_update() {
	if(te_current_renderer==TE_SOFTWARE_RENDERER) {
		te_software_rasterizer_update(software_renderer);
	}
}


//cleaning up
void te_quit() {
	if(software_renderer!=NULL) {
		free(software_renderer);
	}
}
