#pragma once
#include <te.hpp>

namespace t3v
{
	class engine
	{
	private:
		//properties
		//640x480 is standard resolution
		int m_resx=640;
		int m_resy=480;
		bool m_is_fullscreen=false;

		//renderer
		int m_renderer_type=TE_RENDERER_NO_RENDERER; //active renderer
		t3v::renderer m_renderer;
		t3v::software_rasterizer *m_software_rasterizer=NULL;

		//SDL stuff
		SDL_Window *m_window=NULL;

		//input
		SDL_Event m_event;
		uint8_t* m_keyboard_state=NULL;

		engine();
		~engine();

	public:
		//getting data
		int get_resx(){return m_resx;}
		int get_resy(){return m_resy;}

		//setting properties
		void set_resx(int resx){m_resx=resx;}
		void set_resy(int resy){m_resy=resy;}
		void set_fullscreen(bool set_fullscreen){m_is_fullscreen=set_fullscreen;}
		void activate_fps_counter(bool active, t3v::font *font);

		//starting the engine with a renderer
		void start_renderer(int renderer_type);

		//3d rendering stuff
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture); //render a bunch of vertices
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos); //render a bunch of vertices at a certain location
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat); //also at a certain location
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale); //with scaling

		//2d stuff
		void print_single_frame(std::string text, t3v::font& font, t3v::color color_in, int font_size, int x, int y);
		void render2D(SDL_Surface *surface, SDL_Rect& src_rect, SDL_Rect& dst_rect);

		//input
		void update_input();
		bool key_is_pressed(uint8_t scancode); 


		void update();


		engine(const engine&) = delete;
		static engine& get()
		{
			static engine instance;
			return instance;
		}
	};
}