#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_update() {

	//starting the rendering for each thread
	te_thread_barrier_arrive_and_wait(&software_renderer->render_barrier);
	te_thread_barrier_arrive_and_wait(&software_renderer->render_barrier);

	SDL_UpdateWindowSurface(software_renderer->window);

	//clearing the screen
	memset(
		software_renderer->window_surface->pixels, 
		0, 
		software_renderer->resx*software_renderer->resy*TE_COLORDEPTH);
	
	//resetting the triangle render queue
	software_renderer->tri_queue.num_vertices=0;
}
