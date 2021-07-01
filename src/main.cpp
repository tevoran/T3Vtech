#include "te.hpp"



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");
	std::string text="T3Vtech - software renderer";

	t3v::sprite hase_sprite("../assets/Haeschen1.png");


	t3v::object3d box;
	box.make_cube(3);
	box.position({0,0,4});
	t3v::texture *box_tex=t3v::load_texture("../assets/wooden_crate_small.jpg");
	box.use_texture(box_tex);


	//loading assets
	t3v::object2d hase;
	hase.use_sprite(hase_sprite);
	hase.position(900,400);
	hase.scale(4);

	t3v::object2d hase2=hase;
	hase2.position(350,125);
	hase2.scale(40);

	te.activate_fps_counter(true, &font);


	bool quit=false;
	while(!quit)
	{
		box.rotate({1,0,0},0.4);
		box.render();

		//hase2.render();
		hase.render();
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