#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_render_thread(te_software_renderer_thread *thread)
{
	int quit=TE_FALSE;
	while(!quit)
	{
		//if update functions wants the render threads to render then render
		if(software_renderer->currently_rendering==TE_TRUE) {
			for(int i=0; (i*3)<software_renderer->tri_queue.num_vertices; i++) {
				te_software_rasterizer_raster_tri(
					&software_renderer->tri_queue.vertices[i*3],
					&software_renderer->tri_queue.vertices[i*3+1],
					&software_renderer->tri_queue.vertices[i*3+2],
					thread);
			}
		}
		te_thread_barrier_arrive_and_wait(&software_renderer->render_barrier);
			software_renderer->currently_rendering=TE_FALSE;
		te_thread_barrier_arrive_and_wait(&software_renderer->render_barrier);
	}
}