#pragma once
#include <te.hpp>

namespace t3v
{
	struct vertex
	{
		int x=0;
	};

	class engine
	{
	private:
		int m_resx=1920;
		int m_resy=1080;

		//renderer
		int m_renderer_type=TE_RENDERER_NO_RENDERER; //active renderer
		t3v::renderer m_renderer;
		t3v::software_rasterizer* m_software_rasterizer=NULL;

		//SDL stuff
		SDL_Window *m_window=NULL;

		engine();
		~engine();

	public:
		int resx(){return m_resx;}
		int resy(){return m_resy;}

		//rendering stuff
		void choose_renderer(int renderer_type);
		void render(uint8_t r, uint8_t g, uint8_t b);
		void update();


		engine(const engine&) = delete;
		static engine& get()
		{
			static engine instance;
			return instance;
		}
	};
}