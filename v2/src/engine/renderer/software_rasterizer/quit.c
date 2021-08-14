#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_quit()
{
	free(software_renderer->tri_queue.vertices);
	free(software_renderer->threads);
}