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
			int num_vertices=data->rendering_vertex_buffer_ptr->size();
			std::vector<t3v::vertex> vertex=*data->rendering_vertex_buffer_ptr;

			for(int i=0; i<(num_vertices/3); i++) //rendering all the triangles in the queue
			{
				rasterize_triangle(vertex[i*3], vertex[i*3+1], vertex[i*3+2], data);
			}
		}

		//if main thread is executing this function then end it after rendering instead of waiting
		if(data->is_main_thread==true)
		{
			return;
		}
		//synchronizing with the other render threads
		data->render_sync_point->arrive_and_wait();
	}

}