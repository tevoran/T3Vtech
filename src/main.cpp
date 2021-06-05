#include "te.hpp"
#define FRAMES 2000



int main()
{
	t3v::vertex vertex[6];
	//first triangle
	vertex[0].pos.x=0.1;
	vertex[0].pos.y=0.05;
	vertex[0].pos.z=0.1;
	vertex[0].color.r=200;
	vertex[0].color.g=200;
	vertex[0].color.b=0;
	vertex[0].tex.u=25;
	vertex[0].tex.v=0;

	vertex[1].pos.x=0.99;
	vertex[1].pos.y=0.16;
	vertex[1].pos.z=0.1;
	vertex[1].color.r=200;
	vertex[1].color.g=200;
	vertex[1].color.b=0;
	vertex[1].tex.u=0;
	vertex[1].tex.v=0;

	vertex[2].pos.x=0.8;
	vertex[2].pos.y=0.9;
	vertex[2].pos.z=0.1;
	vertex[2].color.r=200;
	vertex[2].color.g=200;
	vertex[2].color.b=0;
	vertex[2].tex.u=0;
	vertex[2].tex.v=25;

	//second triangle
	vertex[3].pos.x=0.1;
	vertex[3].pos.y=0.5;
	vertex[3].pos.z=0.2;
	vertex[3].color.r=50;
	vertex[3].color.g=5;
	vertex[3].color.b=0;
	vertex[3].tex.u=0;
	vertex[3].tex.v=0;

	vertex[4].pos.x=0.8;
	vertex[4].pos.y=0.5;
	vertex[4].pos.z=0.07;
	vertex[4].color.r=50;
	vertex[4].color.g=5;
	vertex[4].color.b=0;
	vertex[4].tex.u=10;
	vertex[4].tex.v=0;

	vertex[5].pos.x=0.03;
	vertex[5].pos.y=0.9;
	vertex[5].pos.z=0.2;
	vertex[5].color.r=50;
	vertex[5].color.g=5;
	vertex[5].color.b=0;
	vertex[5].tex.u=0;
	vertex[5].tex.v=10;

	//third triangle
	vertex[6].pos.x=-10.1;
	vertex[6].pos.y=-0.5;
	vertex[6].pos.z=0.25;
	vertex[6].color.r=50;
	vertex[6].color.g=5;
	vertex[6].color.b=0;
	vertex[6].tex.u=0;
	vertex[6].tex.v=0;

	vertex[7].pos.x=10.8;
	vertex[7].pos.y=-0.5;
	vertex[7].pos.z=0.27;
	vertex[7].color.r=50;
	vertex[7].color.g=5;
	vertex[7].color.b=0;
	vertex[7].tex.u=100;
	vertex[7].tex.v=0;

	vertex[8].pos.x=0.03;
	vertex[8].pos.y=20.9;
	vertex[8].pos.z=0.29;
	vertex[8].color.r=50;
	vertex[8].color.g=5;
	vertex[8].color.b=0;
	vertex[8].tex.u=0;
	vertex[8].tex.v=100;

	t3v::engine& te=t3v::engine::get();
	te.choose_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

	for(int i=0; i<FRAMES; i++)
	{
		te.render(vertex, 9);
		te.update();
	}

	std::chrono::steady_clock::time_point t_end=std::chrono::steady_clock::now();
	std::chrono::duration<float> t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_end-t_begin);
	std::cout << "Time needed for " << FRAMES <<" frames: " << t_delta.count() << "s" << std::endl;
	std::cout << "Which is " << t_delta.count()*1000/FRAMES << "ms per frame" << std::endl;
	std::cout << "Which is " << FRAMES/t_delta.count() << " FPS on average" << std::endl;



	t_begin=std::chrono::steady_clock::now();

	for(int i=0; i<5; i++)
	{
		te.update();
	}

	t_end=std::chrono::steady_clock::now();
	t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_end-t_begin);
	std::cout << "Time needed for " << 5 <<" frames: " << t_delta.count() << "s" << std::endl;
	std::cout << "Which is " << t_delta.count()*1000/5 << "ms per frame" << std::endl;

	//SDL_Delay(1000);
}