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

			uint32_t *z_buffer=NULL;
			std::vector<t3v::vertex> *rendering_vertex_buffer_ptr=NULL;

			bool start_rendering=false; //if this is set to true the thread will start the rendering

			//synchronizing
			t3v::thread::barrier *render_sync_point=NULL;

			//render function variables
			bool is_main_thread=false;
		};

		struct sprite_queue_entry
		{
			SDL_Rect src_rect;
			SDL_Rect dst_rect;
			SDL_Surface *surface=NULL;
		};

		struct text_queue_entry
		{
			SDL_Rect dst_rect;
			SDL_Surface *text_surface=NULL;
		};

		struct clipping_vertices
		{
			int num_vertices=0;
			t3v::vertex vertex[6]; //6 is max possible numbers of vertices
		};

	private:
		bool m_update_necessary=false; //indicate if the update function needs to do something

		//SDL2 related members
		SDL_Surface *m_window_surface=NULL;
		SDL_Window *m_window=NULL;
		
		//Z-Buffer
		uint32_t *m_z_buffer=NULL;

		//render buffer
		std::vector<t3v::vertex> m_rendering_vertex_buffer;

		//sprite render buffer
		std::vector<t3v::software_rasterizer::sprite_queue_entry> m_sprite_render_queue;

		//text render buffer
		std::vector<t3v::software_rasterizer::text_queue_entry> m_text_single_frame_queue;
		t3v::font *m_font=NULL;

		//renderthreads
		int m_num_cpu_threads=0;
		int m_num_render_threads=0;
		std::vector<std::thread> m_thread;
		render_thread_data *m_thread_data=NULL;
		t3v::thread::barrier *m_render_sync_point=NULL;

	private:
		//render pipeline functions
		void vertex_shader(t3v::vertex& vertex, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale);
		void perspective_divide(t3v::vertex& vertex);

		//gives an array of vertices if clipping was necessary
		t3v::software_rasterizer::clipping_vertices clipping(
			t3v::vertex& vertex1,
			t3v::vertex& vertex2,
			t3v::vertex& vertex3); 


		static t3v::color texture_mapping(float u, float v, t3v::texture *texture);
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
		static void draw_pixel_fast_simple(
			uint32_t* pixel_ptr,
			const t3v::color color);

		static void render_thread(render_thread_data *data);
		static void rasterize_triangle(
			t3v::vertex& vertex1,
			t3v::vertex& vertex2,
			t3v::vertex& vertex3,
			render_thread_data *data);

	public:
		software_rasterizer(SDL_Window *window, int num_desired_threads);
		~software_rasterizer();

		//settings
		void activate_fps_counter(bool active, t3v::font *font){m_is_fps_counter_active=active; m_font=font;}

		//2D stuff
		void print_single_frame(std::string text, t3v::font& font, t3v::color color_in, int font_size, int x, int y);
		void render2D(SDL_Surface *surface, SDL_Rect& src_rect, SDL_Rect& dst_rect);

		//render a bunch of vertices at a certain location
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale);
		void update();
	};
}