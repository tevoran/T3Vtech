#include <engine/general.hpp>

#include <te.hpp>


//engine initialization
t3v::engine::engine()
{
	std::cout << "Initializing T3Vtech engine" << std::endl;

	//getting SDL2 working
	std::cout << "Initializing SDL2...";
	if(SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO | 
		SDL_INIT_EVENTS |
		SDL_INIT_JOYSTICK |
		SDL_INIT_HAPTIC |
		SDL_INIT_GAMECONTROLLER)!=0)
	{
		std::cout << "[ERROR] SDL2 couldn't be initialized" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}

	std::cout << "done" << std::endl;

	//getting SDL2_image working
	//The return seems to be kinda buggy on their side
	//might be better to use something different later on
	IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG || IMG_INIT_TIF);
	std::cout << "SDL2_image initialized" << std::endl;

	//starting SDL2_ttf
	if(TTF_Init()!=0)
	{
		std::cout << "[ERROR] error while initializing SDL2_ttf" << std::endl;
		exit(0);
	}
	std::cout << "SDL2_ttf initialized" << std::endl;

	std::cout << "T3Vtech engine successfully initialized" << std::endl;

}

t3v::engine::~engine()
{

/*	if(m_software_rasterizer!=NULL)
	{
		delete m_software_rasterizer;
	}*/
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void t3v::engine::start_renderer(int renderer_type)
{
	//creating the window for the renderer
	if(m_is_fullscreen==true)
	{
		m_window=SDL_CreateWindow("T3Vtech test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_resx, m_resy, SDL_WINDOW_FULLSCREEN);
	}
	else
	{
		m_window=SDL_CreateWindow("T3Vtech test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_resx, m_resy, 0);
	}
	if(m_window==NULL)
	{
		std::cout << "[ERROR] SDL2 couldn't create a window" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}

	std::cout << "Using resolution " << m_resx << "x" << m_resy << std::endl;

	m_renderer_type=renderer_type;

	//creating the right renderer
	switch(renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer = new t3v::software_rasterizer(m_window, 0);
			break;

		case TE_RENDERER_SOFTWARE_RASTERIZER_SINGLE_THREAD:
			m_software_rasterizer = new t3v::software_rasterizer(m_window, 1);
			m_renderer_type=TE_RENDERER_SOFTWARE_RASTERIZER;
			break;
	}

}

//render a bunch of vertices
void t3v::engine::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
		{
			glm::mat4 ident_mat=glm::mat4(1.0f);
			glm::vec3 pos={0,0,0};
			glm::vec3 scale={1,1,1};
			m_software_rasterizer->render(vertices, num_vertices, texture, pos, ident_mat, scale);
			break;
		}
		default:
			m_renderer.render();
			break;
	}
}

//render a bunch of vertices at a certain location
void t3v::engine::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
		{
			glm::mat4 ident_mat=glm::mat4(1.0f);
			glm::vec3 scale={1,1,1};
			m_software_rasterizer->render(vertices, num_vertices, texture, pos, ident_mat, scale);
		}
			break;

		default:
			m_renderer.render();
			break;
	}
}

//render a bunch of vertices at a certain location with a certain rotation
void t3v::engine::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
		{
			glm::vec3 scale={1,1,1};
			m_software_rasterizer->render(vertices, num_vertices, texture, pos, rotation_mat, scale);
		}
			break;

		default:
			m_renderer.render();
			break;
	}
}

//render a bunch of vertices at a certain location with a certain rotation and scaling
void t3v::engine::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->render(vertices, num_vertices, texture, pos, rotation_mat, scale);
			break;

		default:
			m_renderer.render();
			break;
	}
}

void t3v::engine::update()
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->update();
			break;

		default:
			m_renderer.update();
			break;		
	}
}

//2D stuff
void t3v::engine::print_single_frame(std::string text, t3v::font& font, t3v::color color_in, int font_size, int x, int y)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->print_single_frame(text, font, color_in, font_size, x, y);
			break;

		default:
			std::cout << "[ERROR] no renderer is active yet" << std::endl;
			break;		
	}
}

void t3v::engine::render2D(SDL_Surface *surface, SDL_Rect& src_rect, SDL_Rect& dst_rect)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->render2D(surface, src_rect, dst_rect);
			break;

		default:
			std::cout << "[ERROR] no renderer is active yet" << std::endl;
			break;		
	}
}


void t3v::engine::activate_fps_counter(bool active, t3v::font *font)
{
	switch(m_renderer_type)
	{
		case TE_RENDERER_SOFTWARE_RASTERIZER:
			m_software_rasterizer->activate_fps_counter(active, font);
			break;

		default:
			std::cout << "[ERROR] no renderer is active yet" << std::endl;
			break;		
	}
}