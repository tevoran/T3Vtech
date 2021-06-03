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
			for(int i=0; i<(data->num_vertices/3); i++) //rendering all the triangles in the queue
			{
				rasterize_triangle(data->vertex_ptr[i*3], data->vertex_ptr[i*3+1], data->vertex_ptr[i*3+2], data);
			}
		}

		//if main thread is executing this function then end it after rendering
		if(data->is_main_thread==true)
		{
			return;
		}
		//synchronizing with the other render threads
		sync_point(0)->arrive_and_wait();
	}
}