#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_render_tri(
	te_vertex v1,
	te_vertex v2,
	te_vertex v3) {
	//adding the vertices into the render queue
	if(	(software_renderer->tri_queue.num_vertices+3) <
		software_renderer->tri_queue.num_vertices_cap) {
		long int i=software_renderer->tri_queue.num_vertices;
		software_renderer->tri_queue.vertices[i]=v1;

		i++;
		software_renderer->tri_queue.vertices[i]=v2;

		i++;
		software_renderer->tri_queue.vertices[i]=v3;

		i++;
		software_renderer->tri_queue.num_vertices=i;

	}
}