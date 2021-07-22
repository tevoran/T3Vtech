#include <te.h>
#include <SDL2/SDL.h>

void te_software_rasterizer_draw_pixel(
	SDL_Color *pixel_ptr, 
	te_color *pixel_color) {

	*pixel_ptr=*(SDL_Color*)pixel_color;
}