#include "te.hpp"

#define FRAMES 1000


int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(false);
	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");
	std::string text="T3Vtech - software renderer";


	t3v::object3d box;
	box.make_cube(10.3);
	box.position({0,-1.5,3.100});
	t3v::texture *box_tex=t3v::load_texture("../assets/wooden_crate_small.jpg");
	box.use_texture(box_tex);
	box.rotate({1,0,0},90);

	te.activate_fps_counter(true, &font);


	bool quit=false;

	using namespace std::chrono;
	steady_clock::time_point t_old=steady_clock::now();
	for(int i=0; i<FRAMES; i++)
	{
		box.render();
		box.rotate({1,0,0},0.4);
		te.print_single_frame(text, font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

		te.update();

		te.update_input();
		if(te.key_is_pressed(SDL_SCANCODE_ESCAPE))
		{
			quit=true;
		}
		if(quit)
		{
			break;
		}
	}
	steady_clock::time_point t_new=steady_clock::now();
	duration<float> t_delta= duration_cast<duration<float>>(t_new-t_old);

	std::cout << "average frame time: " << t_delta.count()*1000/FRAMES << "ms" << std::endl;
	std::cout << "in " << FRAMES << " frames" << std::endl;

	return 0;
}