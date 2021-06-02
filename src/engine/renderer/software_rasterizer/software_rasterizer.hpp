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
			glm::vec3 vertex1{0.9, 0.1, 0};
			glm::vec3 vertex2{0.1, 0.2, 0};
			glm::vec3 vertex3{0.5, 0.9, 0};
			uint8_t r=0;
			uint8_t g=0;
			uint8_t b=0;
			bool start_rendering=false; //if this is set to true the thread will start the rendering
			struct barycentric_interpolation_optimized_data* bary_data=NULL;

			//render function variables
			bool is_main_thread=false;
		};

	private:
		bool m_update_necessary=false;

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
		static void draw_pixel_fast_64(
			uint64_t* pixel_ptr,
			const uint8_t r, 
			const uint8_t g, 
			const uint8_t b,
			const uint8_t r2, 
			const uint8_t g2, 
			const uint8_t b2);

		static void render_thread(render_thread_data *data);

	public:
		software_rasterizer(SDL_Window *window);
		~software_rasterizer();
		void render(uint8_t r, uint8_t g, uint8_t b);
		void update();
	};
}