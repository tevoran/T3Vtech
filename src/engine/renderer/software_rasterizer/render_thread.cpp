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
			glm::ivec2 pixel1={
				data->vertex1.x*data->resx,
				data->vertex1.y*data->resy
			};

			glm::ivec2 pixel2={
				data->vertex2.x*data->resx,
				data->vertex2.y*data->resy
			};

			glm::ivec2 pixel3={
				data->vertex3.x*data->resx,
				data->vertex3.y*data->resy
			};

			glm::ivec2 pixel_draw={0,0};
			//drawing only if pixel is in drawing area of this thread
			float a,b,c; //barycentric coordinates
			for(int iy = data->y_start; iy < data->y_end; iy++)
			{
				pixel_draw.y=iy;

				for(int ix=0; ix<data->resx; ix++)
				{
					pixel_draw.x=ix;
					t3v::barycentric_interpolation(pixel1, pixel2, pixel3, pixel_draw, a, b, c);
					if(a>0 && a<1 && b>0 && b<1 && c>0 && c<1)
					{
						uint32_t *pixel_ptr=(uint32_t*)data->window_surface->pixels+pixel_draw.x+pixel_draw.y*data->resx;
						draw_pixel_fast(pixel_ptr, data->r, data->g, data->b);
					}
				}
			}
		}

		//synchronizing with the other render threads
		sync_point(0)->arrive_and_wait();
	}
}