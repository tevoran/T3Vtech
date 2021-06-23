#include "te.hpp"
#define FRAMES 1000



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	t3v::texture *crate=t3v::load_texture("../assets/wooden_crate_small.jpg");
	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

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

	te.print("T3Vtech - software renderer", font, {10,240,10, 255}, 32, te.get_resx()-430, te.get_resy()-48);

	for(int i=0; i<FRAMES; i++)
	{
		box.render();
		ground.render();
		te.update();
	}

	std::chrono::steady_clock::time_point t_end=std::chrono::steady_clock::now();
	std::chrono::duration<float> t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_end-t_begin);
	std::cout << "Time needed for " << FRAMES <<" frames: " << t_delta.count() << "s" << std::endl;
	std::cout << "Which is " << t_delta.count()*1000/FRAMES << "ms per frame" << std::endl;
	std::cout << "Which is " << FRAMES/t_delta.count() << " FPS on average" << std::endl;



	t_begin=std::chrono::steady_clock::now();

	for(int i=0; i<10; i++)
	{
		te.update();
	}

	t_end=std::chrono::steady_clock::now();
	t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_end-t_begin);
	std::cout << "Time needed for " << 10 <<" frames: " << t_delta.count() << "s" << std::endl;
	std::cout << "Which is " << t_delta.count()*1000/10 << "ms per frame" << std::endl;

	t3v::free_texture(crate);
	//SDL_Delay(1000);
	return 0;
}