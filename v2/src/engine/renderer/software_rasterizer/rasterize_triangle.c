#include <te.h>

extern te_software_renderer *software_renderer;

void te_software_rasterizer_raster_tri(
	te_vertex *v1,
	te_vertex *v2,
	te_vertex *v3,
	te_software_renderer_thread *thread) {

	//sorting vertices along the y-axis
	if(v1->y > v2->y)
	{
		te_swap(v1, v2);
	}
	if(v2->y > v3->y)
	{
		te_swap(v2, v3);
	}
	if(v1->y > v2->y)
	{
		te_swap(v1, v2);
	}

	//getting the vertices' screen coordinates
	float v1_2d_x=v1->x * software_renderer->resx;
	float v1_2d_y=v1->y * software_renderer->resy;

	float v2_2d_x=v2->x * software_renderer->resx;
	float v2_2d_y=v2->y * software_renderer->resy;

	float v3_2d_x=v3->x * software_renderer->resx;
	float v3_2d_y=v3->y * software_renderer->resy;

	//triangle bounding box
	int y_bb_top=v1_2d_y-1;
	int y_bb_bottom=v3_2d_y+1;

	if(y_bb_bottom < thread->start_y) {
		return;
	}

	if(y_bb_top > thread->end_y) {
		return;
	}

	if(y_bb_top < thread->start_y) {
		y_bb_top < thread->start_y;
	}

	if(y_bb_bottom > thread->end_y) {
		y_bb_bottom = thread->end_y;
	}


	int x_bb_left=v1_2d_x-1;
	int x_bb_right=v1_2d_x+1;
	if(x_bb_left > v2_2d_x) {
		x_bb_left = v2_2d_x-1;
	}
	if(x_bb_left > v3_2d_x) {
		x_bb_left = v3_2d_x-1;
	}

	if(x_bb_right < v2_2d_x) {
		x_bb_right = v2_2d_x+1;
	}
	if(x_bb_right < v3_2d_x) {
		x_bb_right = v3_2d_x+1;
	}

	//crop to the screen
	if(x_bb_left < 0)
	{
		x_bb_left = 0;
	}
	if(x_bb_right > software_renderer->resx) {
		x_bb_right = software_renderer->resx;
	}


	//preparation calculations
	//barycentric coordinates
	float a,b,c;
	float a_line_base,b_line_base,c_line_base;
	float a_delta,b_delta,c_delta;
	float a_line_delta,b_line_delta,c_line_delta;

	te_barycentric_interpolation(
		v1_2d_x,
		v1_2d_y,
		v2_2d_x,
		v2_2d_y,
		v3_2d_x,
		v3_2d_y,
		x_bb_left,
		y_bb_top,
		&a_line_base,
		&b_line_base,
		&c_line_base);

	te_barycentric_interpolation(
		v1_2d_x,
		v1_2d_y,
		v2_2d_x,
		v2_2d_y,
		v3_2d_x,
		v3_2d_y,
		x_bb_left+1,
		y_bb_top,
		&a_delta,
		&b_delta,
		&c_delta);
	a_delta=a_delta - a_line_base;
	b_delta=b_delta - b_line_base;
	c_delta=c_delta - c_line_base;

	te_barycentric_interpolation(
		v1_2d_x,
		v1_2d_y,
		v2_2d_x,
		v2_2d_y,
		v3_2d_x,
		v3_2d_y,
		x_bb_left,
		y_bb_top+1,
		&a_line_delta,
		&b_line_delta,
		&c_line_delta);
	a_line_delta=a_line_delta - a_line_base;
	b_line_delta=b_line_delta - b_line_base;
	c_line_delta=c_line_delta - c_line_base;

	//rasterize triangle
	for(int y=y_bb_top; y<y_bb_bottom; y++) {
		int has_drawn=TE_FALSE;

		//line preparation
		a=a_line_base;
		b=b_line_base;
		c=c_line_base;
		//pixel drawing pointer preparation
		SDL_Color *pixel_ptr=software_renderer->window_surface->pixels;
		pixel_ptr+=x_bb_left + y*software_renderer->resx;

		//go through current line
		for(int x=x_bb_left; x<x_bb_right; x++) {
			//check if pixel is inside triangle
			if(a>0 && b>0 && c>0) {
				has_drawn=TE_TRUE;
				*pixel_ptr=*(SDL_Color*)&v1->color; //draw pixel
			}
			else {
				//if end of the line is reached then stop checking
				if(has_drawn) {
					break;
				}
			}
		//increments per pixel
		a+=a_delta;
		b+=b_delta;
		c+=c_delta;
		pixel_ptr++;
		}
	//increments per line
	a_line_base+=a_line_delta;
	b_line_base+=b_line_delta;
	c_line_base+=c_line_delta;
	}
}