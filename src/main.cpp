#include "te.hpp"
#define FRAMES 2000



int main()
{
	t3v::vertex vertex[3];
	//first triangle
	vertex[0].pos.x=-0.1;
	vertex[0].pos.y=0.1;
	vertex[0].pos.z=0;
	vertex[0].color.r=200;
	vertex[0].color.g=200;
	vertex[0].color.b=0;
	vertex[0].tex.u=0;
	vertex[0].tex.v=0;

	vertex[1].pos.x=0.1;
	vertex[1].pos.y=0.1;
	vertex[1].pos.z=0;
	vertex[1].color.r=200;
	vertex[1].color.g=200;
	vertex[1].color.b=0;
	vertex[1].tex.u=1;
	vertex[1].tex.v=0;

	vertex[2].pos.x=0.1;
	vertex[2].pos.y=-0.1;
	vertex[2].pos.z=0;
	vertex[2].color.r=200;
	vertex[2].color.g=200;
	vertex[2].color.b=0;
	vertex[2].tex.u=1;
	vertex[2].tex.v=1;



	t3v::engine& te=t3v::engine::get();
	//setting properties
	te.set_resx(1920);
	te.set_resy(1080);
	//te.set_fullscreen(true);

	te.start_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	t3v::texture tex=t3v::load_texture("../assets/mexican_tile.jpg");
	t3v::texture wood=t3v::load_texture("../assets/wood.jpg");
	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

	t3v::object3d test_obj;
	test_obj.use_vertices(vertex, 3);
	test_obj.use_texture(&wood);

	for(int i=0; i<FRAMES; i++)
	{
		test_obj.position({0,0,4});
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