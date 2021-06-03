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
			t3v::vertex *vertex_ptr=NULL;
			int num_vertices=0;
			float *z_buffer=NULL;
			bool start_rendering=false; //if this is set to true the thread will start the rendering
			struct barycentric_interpolation_optimized_data* bary_data=NULL;

			//render function variables
			bool is_main_thread=false;
		};

	private:
		bool m_update_necessary=false; //indicate if the update function needs to do something

		//SDL2 related members
		SDL_Surface *m_window_surface=NULL;
		SDL_Window *m_window=NULL;
		
		//Z-Buffer
		float *m_z_buffer=NULL;

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

	private:
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
		static void rasterize_triangle(
			t3v::vertex vertex1,
			t3v::vertex vertex2,
			t3v::vertex vertex3,
			render_thread_data *data);

	public:
		software_rasterizer(SDL_Window *window);
		~software_rasterizer();
		void render(uint8_t r, uint8_t g, uint8_t b);
		void render(t3v::vertex *vertices, const int num_vertices);
		void update();
	};
}