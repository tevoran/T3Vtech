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

		//rendering stuff
		void start_renderer(int renderer_type);
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture); //render a bunch of vertices
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos); //render a bunch of vertices at a certain location
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat); //also at a certain location
		void render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale); //with scaling

		void update();


		engine(const engine&) = delete;
		static engine& get()
		{
			static engine instance;
			return instance;
		}
	};
}