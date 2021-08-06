#include <te.h>
#include <SDL2/SDL.h>
#include <sys/sysinfo.h>

extern SDL_Window *te_window;
extern te_software_renderer *software_renderer;

te_software_renderer* te_software_rasterizer_init() {
	printf("Starting the software rasterizer\n");

	software_renderer=malloc(sizeof(te_software_renderer));

	software_renderer->window=te_window;
	software_renderer->window_surface=SDL_GetWindowSurface(te_window);
	software_renderer->resx=software_renderer->window_surface->w;
	software_renderer->resy=software_renderer->window_surface->h;
	
	printf("Using resolution %ix%i\n",
		software_renderer->resx,
		software_renderer->resy);

	//clearing screen as initialization
	te_software_rasterizer_update(software_renderer);

	//multithreading initialization
	software_renderer->num_procs=te_num_procs();
	printf("Using %i thread(s) for software rasterization\n",
		software_renderer->num_procs);

	return software_renderer;
}
