#include "te.hpp"



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER_SINGLE_THREAD);

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");
	std::string text="T3Vtech - software renderer";


	//loading assets
	t3v::object2d hase;
	hase.load_sprite("../assets/Haeschen1.png");
	hase.position(400,100);
	hase.scale(4);

	t3v::object2d hase2=hase;
	hase2.position(350,125);
	hase2.scale(2);

	te.activate_fps_counter(true, &font);


	bool quit=false;
	while(!quit)
	{
		hase.render();
		hase2.render();
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