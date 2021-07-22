#include <te.h>

void te_software_rasterizer_raster_tri(
	te_vertex v1,
	te_vertex v2,
	te_vertex v3,
	te_software_renderer *software_renderer) {

	//getting the vertices' screen coordinates
	float v1_2d_x=v1.x*software_renderer->resx;
	float v1_2d_y=v1.y*software_renderer->resy;

	float v2_2d_x=v2.x*software_renderer->resx;
	float v2_2d_y=v2.y*software_renderer->resy;

	float v3_2d_x=v3.x*software_renderer->resx;
	float v3_2d_y=v3.y*software_renderer->resy;

	//rasterize triangle
	for(int y=0; y<software_renderer->resy; y++) {
		int has_drawn=TE_FALSE;

		//go through current line
		for(int x=0; x<software_renderer->resx; x++) {
			float a,b,c;
			te_barycentric_interpolation(
				v1_2d_x,
				v1_2d_y,
				v2_2d_x,
				v2_2d_y,
				v3_2d_x,
				v3_2d_y,
				(float)x,
				(float)y,
				&a,
				&b,
				&c);
			//check if pixel is inside triangle
			if(a>0 && b>0 && c>0) {
				has_drawn=TE_TRUE;
				SDL_Color *pixel_ptr=software_renderer->window_surface->pixels;
				pixel_ptr+=x + y*software_renderer->resx;
				te_software_rasterizer_draw_pixel(pixel_ptr, &v1.color);		
			}
			else {
				//if end of the line is reached then stop checking
				if(has_drawn) {
					break;
				}
			}
		}
	}
}