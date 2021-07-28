#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_update() {

	SDL_UpdateWindowSurface(software_renderer->window);

	memset(
		software_renderer->window_surface->pixels, 
		0, 
		software_renderer->resx*software_renderer->resy*4);

}
