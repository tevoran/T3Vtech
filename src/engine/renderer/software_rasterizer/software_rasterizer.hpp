#pragma once
#include <te.hpp>


namespace t3v
{
	class software_rasterizer : public t3v::renderer
	{
	private:
		struct render_thread_data
		{
			int resx=0;
			int resy=0;
			int y_start=0; //the beginning of the drawing space of the thread
			int y_end=0; //the end of the drawing space of the thread
			SDL_Surface *window_surface=NULL;
			
		};

	private:
		SDL_Surface *m_window_surface=NULL;
		SDL_Window *m_window=NULL;
		
		//renderthreads
		int m_num_cpu_threads=0;
		int m_num_render_threads=0;
		std::vector<std::thread> m_thread;

		void draw_pixel_basic(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b);
		static void render_thread(render_thread_data *data);
	public:
		software_rasterizer(SDL_Window *window);
		~software_rasterizer();
		void render();
		void update();
	};
}