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
			//sorting vertices along y-axis
			if(data->vertex1.y > data->vertex2.y)
			{
				std::swap(data->vertex1, data->vertex2);
			}
			if(data->vertex2.y > data->vertex3.y)
			{
				std::swap(data->vertex2, data->vertex3);
			}
			if(data->vertex1.y > data->vertex2.y)
			{
				std::swap(data->vertex1, data->vertex2);
			}

			//converting vertices from clip space to screen space
			glm::ivec2 vertex1_screen{data->vertex1.x*data->resx+0.5,data->vertex1.y*data->resy+0.5};
			glm::ivec2 vertex2_screen{data->vertex2.x*data->resx+0.5,data->vertex2.y*data->resy+0.5};
			glm::ivec2 vertex3_screen{data->vertex3.x*data->resx+0.5,data->vertex3.y*data->resy+0.5};


			//determining bounding box for the render loop
			//this includes the drawing area for this thread
			int x_bounding_start=vertex1_screen.x;
			if(vertex2_screen.x<x_bounding_start)
			{
				x_bounding_start=vertex2_screen.x;
			}
			if(vertex3_screen.x<x_bounding_start)
			{
				x_bounding_start=vertex3_screen.x;
			}
			if(x_bounding_start<0)
			{
				x_bounding_start=0;
			}
			
			int x_bounding_end=vertex1_screen.x;
			if(vertex2_screen.x>x_bounding_end)
			{
				x_bounding_end=vertex2_screen.x;
			}
			if(vertex3_screen.x>x_bounding_end)
			{
				x_bounding_end=vertex3_screen.x;
			}
			if(x_bounding_end>=data->resx)
			{
				x_bounding_end=data->resx;
			}

			int y_bounding_start=vertex1_screen.y;
			if(y_bounding_start<data->y_start)
			{
				y_bounding_start=data->y_start;
			}

			int y_bounding_end=vertex3_screen.y;
			if(y_bounding_end>data->y_end)
			{
				y_bounding_end=data->y_end;
			}

			//determining barycentric division constant for the triangle
			const float div_const=t3v::barycentric_interpolation_optimized_div(vertex1_screen, vertex2_screen, vertex3_screen);

			glm::ivec2 pixel_draw={0,0};
			float a,b,c; //barycentric coordinates
			float d_a,d_b,d_c; //barycentric coordinates
			//rasterizing loop
			for(int iy = y_bounding_start; iy < y_bounding_end; iy++)
			{
				pixel_draw.y=iy;

				bool has_drawn=false; //is used for determining the end of the line
				uint32_t *pixel_ptr=(uint32_t*)data->window_surface->pixels+x_bounding_start+pixel_draw.y*data->resx;

				pixel_draw.x=x_bounding_start;
				t3v::barycentric_interpolation_line_optimized(
					vertex1_screen,
					vertex2_screen,
					vertex3_screen,
					pixel_draw,
					div_const,
					a, b, c,
					d_a, d_b, d_c);


				for(int ix=x_bounding_start; ix<x_bounding_end; ix++)
				{
					a+=d_a;
					b+=d_b;
					c+=d_c;
					if(a>0 && a<1 && b>0 && b<1 && c>0)
					{
						has_drawn=true;
						draw_pixel_fast(pixel_ptr, data->r, data->g, data->b);
					}
					else
					{
						//if end of line is reached then go to next line
						if(has_drawn==true)
						{
							break;
						}
					}
					pixel_ptr++;
				}
			}
		}

		if(data->is_main_thread==true)
		{
			return;
		}
		//synchronizing with the other render threads
		sync_point(0)->arrive_and_wait();
	}
}