#include <te.hpp>


t3v::software_rasterizer::software_rasterizer(SDL_Window *window, int num_desired_threads)
{
	std::cout << "Initializing software rasterizer" << std::endl;

	m_window=window;
	m_window_surface=SDL_GetWindowSurface(window);
	if(m_window_surface==NULL)
	{
		std::cout << "[ERROR] software rasterizer can't get the window surface to draw on" << std::endl;
		exit(0);
	}

	m_resx=m_window_surface->w;
	m_resy=m_window_surface->h;

	//clearing screen
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black

	//creating z-buffer
	m_z_buffer = new uint32_t[m_resx*m_resx];
	memset(m_z_buffer, 0xFF, m_resx*m_resy*sizeof(uint32_t)); //writes MAX_INT32 to each entry in the z-buffer

	//setting up projection matrix
	m_projection_mat = glm::perspective(m_fov, (float)m_resx/(float)m_resy, m_near_z_clip, m_far_z_clip);


	//creating render threads
	m_num_cpu_threads=std::thread::hardware_concurrency();
	if(num_desired_threads>0 && num_desired_threads<m_num_cpu_threads)
	{
		m_num_cpu_threads=num_desired_threads;
	}
	
	m_num_render_threads=m_num_cpu_threads-1;		

	std::cout << "Using " << m_num_cpu_threads << " thread(s) for software rasterizing" << std::endl;
	m_thread_data= new render_thread_data[m_num_cpu_threads];

	//creating barrier
	static t3v::thread::barrier new_barrier(m_num_cpu_threads);
	m_render_sync_point=&new_barrier;

	//multithreaded
	if(m_num_cpu_threads>1)
	{
		for(int i=0; i<m_num_cpu_threads; i++)
		{
			m_thread_data[i].resx=m_resx;
			m_thread_data[i].resy=m_resy;
			m_thread_data[i].y_start=(i)*m_resy/m_num_cpu_threads;
			m_thread_data[i].y_end=(i+1)*m_resy/m_num_cpu_threads;
			m_thread_data[i].window_surface=m_window_surface;
			m_thread_data[i].start_rendering=false;
			m_thread_data[i].rendering_vertex_buffer_ptr=&m_rendering_vertex_buffer;
			m_thread_data[i].render_sync_point=m_render_sync_point;

			if(i<m_num_render_threads)
			{
				m_thread.push_back(std::thread(render_thread, &m_thread_data[i]));
			}
		}
		m_render_sync_point->arrive_and_wait();
	}
	//single threaded
	else
	{
		m_thread_data[0].resx=m_resx;
		m_thread_data[0].resy=m_resy;
		m_thread_data[0].y_start=0;
		m_thread_data[0].y_end=m_resy;
		m_thread_data[0].window_surface=m_window_surface;
		m_thread_data[0].start_rendering=false;
		m_thread_data[0].rendering_vertex_buffer_ptr=&m_rendering_vertex_buffer;
		m_thread_data[0].render_sync_point=m_render_sync_point;

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

	delete [] m_z_buffer;
}


void t3v::software_rasterizer::update()
{
	//rendering 3D stuff
	if(m_update_necessary==true) //if update is necessary then render everything
	{
		if(m_num_cpu_threads>0)
		{
			for(int i=0; i<m_num_cpu_threads; i++)
			{
				m_thread_data[i].start_rendering=true;
				m_thread_data[i].z_buffer=m_z_buffer;
				m_thread_data[i].rendering_vertex_buffer_ptr=&m_rendering_vertex_buffer;
				m_thread_data[i].start_rendering=true;
			}
			m_render_sync_point->arrive_and_wait(); //let the render threads work

			//let main thread render alongside the other threads
			m_thread_data[m_num_cpu_threads-1].is_main_thread=true;
			render_thread(&m_thread_data[m_num_cpu_threads-1]);

			m_render_sync_point->arrive_and_wait(); //continue
		}
	}
	m_update_necessary=false;

	//rendering text queue
	//rendering FPS counter
	if(m_is_fps_counter_active==true)
	{
		static std::chrono::steady_clock::time_point t_old=std::chrono::steady_clock::now();
		std::chrono::steady_clock::time_point t_new=std::chrono::steady_clock::now();
		std::chrono::duration<float> t_delta=std::chrono::duration_cast<std::chrono::duration<float>>(t_new-t_old);
		t_old=t_new;

		std::string FPS_count = std::to_string(1/t_delta.count());
		std::string FPS_count_add = " FPS";
		FPS_count = FPS_count + FPS_count_add;
		print_single_frame(FPS_count, *m_font, {10,240,10, 255}, 32, 0, 0);
	}

	//sprite render queue
	for(int i=0; i<m_sprite_render_queue.size(); i++)
	{
		SDL_BlitScaled(m_sprite_render_queue[i].surface, &m_sprite_render_queue[i].src_rect, m_window_surface, &m_sprite_render_queue[i].dst_rect);
	}
	m_sprite_render_queue.erase(m_sprite_render_queue.begin(), m_sprite_render_queue.begin()+m_sprite_render_queue.size());

	//single frame text
	for(int i=0; i<m_text_single_frame_queue.size(); i++)
	{
		SDL_BlitSurface(m_text_single_frame_queue[i].text_surface, NULL, m_window_surface, &m_text_single_frame_queue[i].dst_rect);
		SDL_FreeSurface(m_text_single_frame_queue[i].text_surface); //free the surface after usage
	}
	m_text_single_frame_queue.erase(m_text_single_frame_queue.begin(), m_text_single_frame_queue.begin()+m_text_single_frame_queue.size());

	if(SDL_UpdateWindowSurface(m_window)!=0)
	{
		std::cout << "[ERROR] Couldn't update window surface anymore" << std::endl;
		std::cout << "SDL2 error message:" << std::endl << SDL_GetError() << std::endl;
		exit(0);
	}

	//clearing buffers
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black
	memset(m_z_buffer, 0xFF, m_resx*m_resy*sizeof(uint32_t)); //resetting z_buffer
	m_rendering_vertex_buffer.erase(m_rendering_vertex_buffer.begin(), m_rendering_vertex_buffer.end()); 	//clearing rendering vertex buffer
}