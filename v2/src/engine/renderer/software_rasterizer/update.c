#include <te.h>


void te_software_rasterizer_update(te_software_renderer *software_renderer) {

	SDL_UpdateWindowSurface(software_renderer->window);

	memset(
		software_renderer->window_surface->pixels, 
		0, 
		software_renderer->resx*software_renderer->resy*4);

}
