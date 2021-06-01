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
			glm::vec3 vertex{0.3, 0.3, 0};
			bool ready=true; //shows if the thread has done everything so far
			bool start_rendering=false; //if this is set to true the thread will start the rendering
		};

	private:
		SDL_Surface *m_window_surface=NULL;
		SDL_Window *m_window=NULL;
		
		//renderthreads
		int m_num_cpu_threads=0;
		int m_num_render_threads=0;
		std::vector<std::thread> m_thread;
		render_thread_data *m_thread_data=NULL;
		static auto sync_point(int num_threads)
			{
				static std::barrier sync_point(num_threads, []{});
				return &sync_point;
			}

		void draw_pixel_basic(const int x, const int y, const uint8_t r, const uint8_t g, const uint8_t b);
		static void draw_pixel_fast(uint32_t* pixel_ptr, const uint8_t r,	const uint8_t g, const uint8_t b);

		static void render_thread(render_thread_data *data);

	public:
		software_rasterizer(SDL_Window *window);
		~software_rasterizer();
		void render();
		void update();
	};
}