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

	t3v::texture crate=t3v::load_texture("../assets/wooden_crate_small.jpg");
	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

	int num_cubes=100;
	t3v::object3d test_obj[num_cubes];

	for(int i=0; i<num_cubes; i++)
	{
		test_obj[i].make_cube(1);
		test_obj[i].use_texture(&crate);
		test_obj[i].position({(float)i*3*cos(i),(float)i*1.5*sin((float)i*PI*2/5),i*2+2});
	}

	for(int i=0; i<FRAMES; i++)
	{
		test_obj[0].rotate({0,1,0}, 0.3);
		for(int i=0; i<num_cubes; i++)
		{
			test_obj[i].render();
		}
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