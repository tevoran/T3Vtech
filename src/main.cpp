#include "te.hpp"



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1366);
	te.set_resy(768);
	te.set_fullscreen(false);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");


	te.activate_fps_counter(true, &font);


	bool quit=false;
	while(!quit)
	{
		std::string text="T3Vtech - software renderer";
		te.print_single_frame(text, font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

		te.update();

		te.update_input();
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
		}
	}

	return 0;
}