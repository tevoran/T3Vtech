#include "te.hpp"
#define FRAMES 2000

int main()
{
	t3v::engine& te=t3v::engine::get();
	te.choose_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);

	std::chrono::steady_clock::time_point t_begin=std::chrono::steady_clock::now();

	for(int i=0; i<FRAMES; i++)
	{
		te.render(sin(((float)i/100))*55+200, sin(((float)i/150))*30+70, 0);
		te.update();
	}

	std::chrono::steady_clock::time_point t_end=std::chrono::steady_clock::now();
	std::chrono::duration<float> t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_end-t_begin);
	std::cout << "Time needed for " << FRAMES <<" frames: " << t_delta.count() << "s" << std::endl;
	std::cout << "Which is " << t_delta.count()*1000/FRAMES << "ms per frame" << std::endl;



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