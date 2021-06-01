#include "te.hpp"

int main()
{
	t3v::engine& te=t3v::engine::get();
	te.choose_renderer(TE_RENDERER_SOFTWARE_RASTERIZER);
	te.render();
	te.update();
	te.render();
	te.update();


	SDL_Delay(3000);
}