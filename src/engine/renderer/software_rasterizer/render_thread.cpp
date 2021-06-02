#include <te.hpp>

void t3v::software_rasterizer::render_thread(render_thread_data *data)
{
	while(true)
	{
		//rendering when thread is commanded to render
		if(data->start_rendering==true)
		{
			data->start_rendering=false;

			//actual rendering part
			glm::ivec2 pixel={
				data->vertex.x*data->resx,
				data->vertex.y*data->resy
			};
			if(pixel.y>=data->y_start && pixel.y<data->y_end)
			{
				uint32_t *pixel_ptr=(uint32_t*)data->window_surface->pixels+pixel.x+pixel.y*data->resx;
				draw_pixel_fast(pixel_ptr, data->r, data->g, data->b);
			}
		}
		//synchronizing with the other render threads
		sync_point(0)->arrive_and_wait();
	}
}