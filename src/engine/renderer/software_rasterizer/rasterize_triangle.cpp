#include <te.hpp>

void t3v::software_rasterizer::rasterize_triangle(
	t3v::vertex vertex1,
	t3v::vertex vertex2,
	t3v::vertex vertex3,
	render_thread_data *data)
{
	//sorting vertices along y-axis
	if(vertex1.pos.y > vertex2.pos.y)
	{
		std::swap(vertex1, vertex2);
	}
	if(vertex2.pos.y > vertex3.pos.y)
	{
		std::swap(vertex2, vertex3);
	}
	if(vertex1.pos.y > vertex2.pos.y)
	{
		std::swap(vertex1, vertex2);
	}

	//converting vertices from clip space to screen space
	glm::ivec2 vertex1_screen{vertex1.pos.x*data->resx+0.5,vertex1.pos.y*data->resy+0.5};
	glm::ivec2 vertex2_screen{vertex2.pos.x*data->resx+0.5,vertex2.pos.y*data->resy+0.5};
	glm::ivec2 vertex3_screen{vertex3.pos.x*data->resx+0.5,vertex3.pos.y*data->resy+0.5};


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
			if(a>0 && b>0 && c>0)
			{
				//z-buffer check
				float current_z=t3v::barycentric_interpolate_value(a,b,c,vertex1.pos.z,vertex2.pos.z,vertex3.pos.z);
				int offset=ix+iy*data->resx;
				if((current_z<data->z_buffer[offset] && current_z>0) || data->z_buffer[offset]==0)
				{
					//writing z-buffer value
					data->z_buffer[offset]=current_z;
					has_drawn=true;
					draw_pixel_fast(pixel_ptr, vertex1.color.r, vertex1.color.g, vertex1.color.b);
				}
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