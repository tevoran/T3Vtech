#include "te.hpp"
#define FRAMES 2000



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	t3v::texture *crate=t3v::load_texture("../assets/wooden_crate_small.jpg");

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");

	t3v::object3d box;
	box.make_cube(3);
	box.position({-2.5,0,4});
	box.use_texture(crate);

	t3v::texture *road_tex=t3v::load_texture("../assets/road.png");
	t3v::object3d ground;
	ground.make_quad(20, 20);
	ground.position({0,-1.5,10.1});
	ground.rotate({1,0,0}, 90);
	ground.use_texture(road_tex);

	t3v::texture *sky_tex=t3v::load_texture("../assets/Sky-072.jpg");
	t3v::object3d sky;
	sky.make_quad(160, 90);
	sky.position({0,40,20});
	sky.use_texture(sky_tex);

	te.activate_fps_counter(true, &font);
	for(int i=0; i<FRAMES; i++)
	{
		box.render();
		ground.render();
		sky.render();

		std::string text="T3Vtech - software renderer";
		te.print_single_frame(text, font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

		te.update();
	}



	t3v::free_texture(crate);
	t3v::free_texture(road_tex);
	//SDL_Delay(1000);
	return 0;
}