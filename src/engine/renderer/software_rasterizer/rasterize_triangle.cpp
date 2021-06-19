#include <te.hpp>

void t3v::software_rasterizer::rasterize_triangle(
	t3v::vertex& vertex1,
	t3v::vertex& vertex2,
	t3v::vertex& vertex3,
	render_thread_data *data)
{
	//converting vertices from clip space to screen space
	//triangle is artificially stretched to avoid empty spaces between adjacent triangles
	glm::i32vec2 vertex1_screen{vertex1.pos.x*data->resx+0.0,vertex1.pos.y*data->resy+0.0};
	glm::i32vec2 vertex3_screen{vertex3.pos.x*data->resx+1.0,vertex3.pos.y*data->resy+1.0};
	glm::i32vec2 vertex2_screen;
	if(vertex2.pos.x>vertex1.pos.x)
	{
		vertex2_screen=glm::i32vec2{vertex2.pos.x*data->resx+1.0,vertex2.pos.y*data->resy+0.0};
	}
	else if(vertex2.pos.x<vertex1.pos.x)
	{
		vertex2_screen=glm::i32vec2{vertex2.pos.x*data->resx+0.0,vertex2.pos.y*data->resy+1.0};
	}
	else
	{
		vertex2_screen=glm::i32vec2{vertex2.pos.x*data->resx+0.5,vertex2.pos.y*data->resy+0.5};		
	}

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
	//barycentric coordinates
	float a,b,c; 
	float d_a,d_b,d_c; //barycentric coordinates increment

	//texture coordinates
	float u,v;
	float u_tmp, v_tmp;
	float u_delta, v_delta;

	//perspective correct interpolation
	float w_inv;
	float w_inv_delta;

	//rasterizing loop
	for(int iy = y_bounding_start; iy < y_bounding_end; iy++)
	{
		pixel_draw.y=iy;

		bool has_drawn=false; //is used for determining the end of the line
		uint32_t *pixel_ptr=(uint32_t*)data->window_surface->pixels+x_bounding_start+pixel_draw.y*data->resx;

		pixel_draw.x=x_bounding_start;

		//barycentric coordinates line preparation
		t3v::barycentric_interpolation_line_optimized(
			vertex1_screen,
			vertex2_screen,
			vertex3_screen,
			pixel_draw,
			div_const,
			a, b, c,
			d_a, d_b, d_c);

		//perspective correct interpolation line preparation
		w_inv=t3v::barycentric_interpolate_value(a,b,c,vertex1.pos.w,vertex2.pos.w,vertex3.pos.w);
		float w_tmp=t3v::barycentric_interpolate_value(a+d_a,b+d_b,c+d_c,vertex1.pos.w,vertex2.pos.w,vertex3.pos.w);
		w_inv_delta=w_tmp-w_inv;


		//z-buffering line preparation
		//INT32_MAX is my max used z-buffer value for optimal clipping
		float z_tmp_1=t3v::barycentric_interpolate_value(a,b,c,vertex1.pos.z,vertex2.pos.z,vertex3.pos.z);
		uint32_t z=z_tmp_1*INT32_MAX; //calculating line beginning

		float z_tmp_2=t3v::barycentric_interpolate_value(a+d_a,b+d_b,c+d_c,vertex1.pos.z,vertex2.pos.z,vertex3.pos.z);

		uint32_t z_tmp_int_2=z_tmp_2*INT32_MAX;

		int32_t z_delta=z_tmp_int_2-z; //calculating difference for each following pixel in a line
		int offset=x_bounding_start+iy*data->resx; //pixel offset in the z-buffer

		//rendering a line
		for(int ix=x_bounding_start; ix<x_bounding_end; ix++)
		{
			if(a>=0 && b>=0 && c>=0 && z<INT32_MAX) //z value buffer overflow check for clipping
			{
				//z-buffer check
				if(z < data->z_buffer[offset])
				{
					//writing z-buffer value
					data->z_buffer[offset]=z;

					//this is the first pixel that is drawn in the line
					//texture coordinates
					if(has_drawn==false)
					{
						//texture coordinates interpolation preparation
						u=t3v::barycentric_interpolate_value(a,b,c,vertex1.tex.u,vertex2.tex.u,vertex3.tex.u);
						v=t3v::barycentric_interpolate_value(a,b,c,vertex1.tex.v,vertex2.tex.v,vertex3.tex.v);
						u_tmp=t3v::barycentric_interpolate_value(a+d_a,b+d_b,c+d_c,vertex1.tex.u,vertex2.tex.u,vertex3.tex.u);
						v_tmp=t3v::barycentric_interpolate_value(a+d_a,b+d_b,c+d_c,vertex1.tex.v,vertex2.tex.v,vertex3.tex.v);
						u_delta=u_tmp-u;
						v_delta=v_tmp-v;
					}

					float w=1/w_inv;
					t3v::color pixel_color=texture_mapping(u*w, v*w, vertex1.texture);
					has_drawn=true;
					draw_pixel_fast_simple(pixel_ptr, pixel_color);
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
			//line increments
			//barycentric coordinates line increments
			a+=d_a;
			b+=d_b;
			c+=d_c;

			//z-buffer line increments
			z+=z_delta;

			//pixel pointer increment
			offset++;

			//perspective correction increment
			w_inv+=w_inv_delta;

			//texture coordinates increment;
			u+=u_delta;
			v+=v_delta;

			//pixel draw pointer increment
			pixel_ptr++;
		}
	}
}