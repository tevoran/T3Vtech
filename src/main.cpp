#include "te.hpp"
#define FRAMES 5000



int main()
{
	t3v::engine& te=t3v::engine::get();
	
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	t3v::texture tex=t3v::load_texture("../assets/mexican_tile.jpg");
	t3v::texture wood=t3v::load_texture("../assets/wood.jpg");
	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

	t3v::object3d test_obj;
	test_obj.make_quad(1,1);
	test_obj.use_texture(&wood);

	for(int i=0; i<FRAMES; i++)
	{
		test_obj.position({0,0,2});
		test_obj.rotate({1,0,0}, 0.3);
		test_obj.render();
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

	//SDL_Delay(1000);
	return 0;
}