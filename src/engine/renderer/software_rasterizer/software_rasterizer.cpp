#include <te.hpp>


t3v::software_rasterizer::software_rasterizer(SDL_Window *window)
{
	std::cout << "Initializing software rasterizer" << std::endl;

	m_window=window;
	m_window_surface=SDL_GetWindowSurface(window);
	if(m_window_surface==NULL)
	{
		std::cout << "[ERROR] software rasterizer can't get the window surface to draw on" << std::endl;
		exit(0);
	}
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black

	m_resx=m_window_surface->w;
	m_resy=m_window_surface->h;

	//creating render threads
	m_num_cpu_threads=std::thread::hardware_concurrency();
	if(m_num_cpu_threads>1)
	{
		m_num_render_threads=m_num_cpu_threads-1;		
		std::cout << "Using " << m_num_cpu_threads << " threads for software rasterizing" << std::endl;
		m_thread_data= new render_thread_data[m_num_cpu_threads];
		sync_point(m_num_cpu_threads); //creating barrier

		for(int i=0; i<m_num_cpu_threads; i++)
		{
			m_thread_data[i].resx=m_resx;
			m_thread_data[i].resy=m_resy;
			m_thread_data[i].y_start=(i)*m_resy/m_num_cpu_threads;
			m_thread_data[i].y_end=(i+1)*m_resy/m_num_cpu_threads;
			m_thread_data[i].window_surface=m_window_surface;
			m_thread_data[i].start_rendering=false;

			m_thread.push_back(std::thread(render_thread, &m_thread_data[i]));
		}
		sync_point(0)->arrive_and_wait(); //synchronizing threads
	}
	else
	{
		std::cout << "[ERROR] Currently only multithreaded software rasterizing is supported" << std::endl;
		exit(0);
	}
	std::cout << "Software rasterizer successfully initialized" << std::endl;
}

t3v::software_rasterizer::~software_rasterizer()
{
	//destroying render threads if necessary
	if(m_num_render_threads>0)
	{
		for(int i=m_num_render_threads; i>=0; i--)
		{
			m_thread[i].join();
		}
		delete [] m_thread_data;
	}
}

void t3v::software_rasterizer::render(uint8_t r, uint8_t g, uint8_t b)
{
	m_update_necessary=true;
	if(m_num_render_threads>0)
	{
		for(int i=0; i<m_num_cpu_threads; i++)
		{
			m_thread_data[i].r=r;
			m_thread_data[i].g=g;
			m_thread_data[i].b=b;
		}
	}
}

void t3v::software_rasterizer::update()
{
	if(m_update_necessary==true) //if update is necessary then render everything
	{
		if(m_num_cpu_threads>0)
		{
			for(int i=0; i<m_num_cpu_threads; i++)
			{
				m_thread_data[i].start_rendering=true;			
			}
			sync_point(0)->arrive_and_wait(); //let the threads work

			//let main thread render alongside the other threads
			m_thread_data[m_num_cpu_threads-1].is_main_thread=true;
			render_thread(&m_thread_data[m_num_cpu_threads-1]);

			sync_point(0)->arrive_and_wait(); //continue 
		}
	}
	m_update_necessary=false;

	if(SDL_UpdateWindowSurface(m_window)!=0)
	{
		std::cout << "[ERROR] Couldn't update window surface anymore" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black
}