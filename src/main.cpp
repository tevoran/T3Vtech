#include "te.hpp"
#define FRAMES 1000



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1366);
	te.set_resy(768);
	te.set_fullscreen(false);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	t3v::texture *crate=t3v::load_texture("../assets/wooden_crate_small.jpg");

	//reading test font
	t3v::font font("../assets/fonts/OpenSans-Regular.ttf");

	t3v::object3d box;
	box.make_cube(3);
	box.position({-2.5,0,4});
	box.use_texture(crate);

	t3v::texture *road_tex=t3v::load_texture("../assets/road.jpg");
	t3v::object3d ground;
	ground.make_quad(20, 20);
	ground.position({0,-1.5,10.1});
	ground.rotate({1,0,0}, 90);
	ground.use_texture(road_tex);


	for(int i=0; i<FRAMES; i++)
	{
		box.render();
		ground.render();

		
		te.print_single_frame("T3Vtech - software renderer", font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

		//FPS counter
		static std::chrono::steady_clock::time_point t_old=std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point t_new=std::chrono::steady_clock::now();
		std::chrono::duration<float> t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_new-t_old);
		t_old=t_new;

		std::string FPS_count = std::to_string(1/t_delta.count());
		std::string FPS_count_add = " FPS";
		FPS_count = FPS_count + FPS_count_add;
		te.print_single_frame(FPS_count, font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-96);

		te.update();
	}



	t3v::free_texture(crate);
	t3v::free_texture(road_tex);
	//SDL_Delay(1000);
	return 0;
}