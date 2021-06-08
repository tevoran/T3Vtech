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

	//creating z-buffer
	m_z_buffer = new uint32_t[m_resx*m_resx];
	memset(m_z_buffer, 0xFF, m_resx*m_resy*sizeof(uint32_t)); //writes MAX_INT32 to each entry in the z-buffer

	//setting up projection matrix
	m_projection_mat[0].x=tan(0.5*PI-0.5*m_fov);
	m_projection_mat[0].y=0;
	m_projection_mat[0].z=0;
	m_projection_mat[0].w=0;

	m_projection_mat[1].x=0;
	m_projection_mat[1].y=((float)m_resx/(float)m_resy)*tan(0.5*PI-0.5*m_fov);
	m_projection_mat[1].z=0;
	m_projection_mat[1].w=0;

	m_projection_mat[2].x=0;
	m_projection_mat[2].y=0;
	m_projection_mat[2].z=(1.0-m_near_z_clip)/(m_far_z_clip-m_near_z_clip);
	m_projection_mat[2].w=0;

	m_projection_mat[3].x=0;
	m_projection_mat[3].y=0;
	m_projection_mat[3].z=0;
	m_projection_mat[3].w=1;

	m_projection_mat = glm::perspective(m_fov, (float)m_resx/(float)m_resy, 0.1f, 150.0f);
	std::cout << glm::to_string(m_projection_mat) << std::endl;
	//creating render threads
	m_num_cpu_threads=std::thread::hardware_concurrency();

	m_num_render_threads=m_num_cpu_threads-1;		

	std::cout << "Using " << m_num_cpu_threads << " thread(s) for software rasterizing" << std::endl;
	m_thread_data= new render_thread_data[m_num_cpu_threads];
	sync_point(m_num_cpu_threads); //creating barrier

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


			m_thread.push_back(std::thread(render_thread, &m_thread_data[i]));
		}
		sync_point(0)->arrive_and_wait(); //synchronizing threads
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


void t3v::software_rasterizer::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture)
{
	//writing to rendering vertex buffer
	for(int i=0; i<num_vertices/3; i++)
	{
		//adding texture
		t3v::vertex vertex1 = vertices[i*3];
			vertex1.texture=texture;
		t3v::vertex vertex2 = vertices[i*3+1];
			vertex2.texture=texture;
		t3v::vertex vertex3 = vertices[i*3+2];
			vertex3.texture=texture;

		//applying vertexshader
		vertex_shader(vertex1);
		vertex_shader(vertex2);
		vertex_shader(vertex3);

		//sorting vertices along y-axis
		if(vertex1.pos.y > vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}
		if(vertex2.pos.y > vertex3.pos.y)
		{
			std::swap(vertex2, vertex3);
		}
		if(vertex1.pos.y > vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}

		m_rendering_vertex_buffer.push_back(vertex1);
		m_rendering_vertex_buffer.push_back(vertex2);
		m_rendering_vertex_buffer.push_back(vertex3);
	}

	m_update_necessary=true;
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
				m_thread_data[i].z_buffer=m_z_buffer;
				m_thread_data[i].rendering_vertex_buffer_ptr=&m_rendering_vertex_buffer;
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

	//clearing buffers
	memset(m_window_surface->pixels, 0, m_resx*m_resy*sizeof(uint32_t)); //clearing the screen to black
	memset(m_z_buffer, 0xFF, m_resx*m_resy*sizeof(uint32_t)); //resetting z_buffer
	m_rendering_vertex_buffer.erase(m_rendering_vertex_buffer.begin(), m_rendering_vertex_buffer.end()); 	//clearing rendering vertex buffer
}