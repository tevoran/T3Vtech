#ifndef TE_SOFTWARE_RASTERIZER_H
#define TE_SOFTWARE_RASTERIZER_H

#include <SDL2/SDL.h>
#include <threads.h>

#define te_software_renderer_draw_pixel(x, y, c) pixels[x + w*(y)] = c

//the triangle vertex queue for the render threads
struct te_software_renderer_tri_queue {
	te_vertex *vertices;
	long int num_vertices_cap;
	long int num_vertices;
} typedef te_software_renderer_tri_queue;

//render thread specific data
struct te_software_renderer_thread {
	thrd_t current_thread;
	int resx;
	int start_y;
	int end_y;
	bool currently_rendering;
} typedef te_software_renderer_thread;

//using the struct as a collection of data for the software renderer
struct te_software_renderer {
	SDL_Window *window;
	SDL_Surface *window_surface;
	int resx;
	int resy;
	int num_procs;
	int num_threads;
	te_software_renderer_thread *threads;
	te_software_renderer_tri_queue tri_queue;
	bool currently_rendering;
	te_thread_barrier render_barrier;
} typedef te_software_renderer;


te_software_renderer* te_software_rasterizer_init();
void te_software_rasterizer_quit();
void te_software_rasterizer_update();

void te_software_rasterizer_render_tri(
	te_vertex v1,
	te_vertex v2,
	te_vertex v3);
void te_software_rasterizer_render_thread(te_software_renderer_thread *thread);
void te_software_rasterizer_raster_tri(
	te_vertex *v1,
	te_vertex *v2,
	te_vertex *v3,
	te_software_renderer_thread *thread);


#endif