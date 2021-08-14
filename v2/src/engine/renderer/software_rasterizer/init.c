#include <te.h>
#include <SDL2/SDL.h>

extern SDL_Window *te_window;
extern te_software_renderer *software_renderer;

te_software_renderer* te_software_rasterizer_init() {
	printf("Starting the software rasterizer\n");

	//gets deallocated when te_quit() gets executed
	software_renderer=malloc(sizeof(te_software_renderer));

	software_renderer->window=te_window;
	software_renderer->window_surface=SDL_GetWindowSurface(te_window);
	software_renderer->resx=software_renderer->window_surface->w;
	software_renderer->resy=software_renderer->window_surface->h;
	software_renderer->currently_rendering=TE_FALSE;
	
	printf("Using resolution %ix%i\n",
		software_renderer->resx,
		software_renderer->resy);

	//initializing triangle render queue
	//memory gets free'd in quit.c
	software_renderer->tri_queue.num_vertices=0;
	software_renderer->tri_queue.num_vertices_cap=10000;
	software_renderer->tri_queue.vertices=malloc(sizeof(te_vertex)
		* software_renderer->tri_queue.num_vertices_cap);

	//clearing screen as initialization
	te_software_rasterizer_update();


	//multithreading initialization
	software_renderer->num_procs=te_num_procs();
	printf("Using %i thread(s) for software rasterization\n",
		software_renderer->num_procs);

	software_renderer->render_barrier=te_thread_barrier_init(
		software_renderer->num_procs);

	//gets deallocated in quit.c
	software_renderer->threads=
		malloc(
			sizeof(te_software_renderer_thread)
			* software_renderer->num_procs);

	for(int i=0; i<(software_renderer->num_procs-1); i++) {
		//determining the respective chunk of the screen for each thread
		software_renderer->threads[i].start_y=
			(float)((float)i/software_renderer->num_procs)
			* software_renderer->resy;
		software_renderer->threads[i].end_y=
			(float)(((float)i+1)/software_renderer->num_procs)
			* software_renderer->resy;
		
		if( thrd_create(
			&software_renderer->threads[i].current_thread,
			(thrd_start_t)te_software_rasterizer_render_thread,
			&software_renderer->threads[i])
			!=thrd_success) {
			
			printf("ERROR: couldn't create thread\n");
			}
	}
	te_thread_barrier_arrive_and_wait(&software_renderer->render_barrier);
	return software_renderer;
}
