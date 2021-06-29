#include <te.hpp>

t3v::thread::barrier::barrier(const uint32_t num_threads)
{
	m_num_threads.store(num_threads);
	if(m_release_flag.size()==0)
	{
		m_release_flag.push_back({std::this_thread::get_id(), false});
	}

	m_still_waiting_for.store(num_threads);
	m_already_released.store(0);
	m_release.store(false);

}

void t3v::thread::barrier::arrive_and_wait()
{
	m_mutex_register_thread.lock();

	//if there have been less than required threads registered
	if(m_release_flag.size()<m_num_threads.load())
	{
		for(int i=0; i<m_release_flag.size(); i++)
		{ 
			if(m_release_flag[i].thread_id==std::this_thread::get_id())
			{
				break; //already an entry
			}
			if(i==(m_release_flag.size()-1))
			{
				m_release_flag.push_back({std::this_thread::get_id(), false});
				if(m_release_flag.size()==m_num_threads.load())
				{
					std::cout << "all threads registered" << std::endl;
				}
			}
		}	
	}

	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " will unlock the register lock" << std::endl;
		}
	}
	m_mutex_register_thread.unlock();


	//setting release flag
	m_mutex_set_local_flag.lock();
	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " set its release flag" << std::endl;
			m_release_flag[i].local_release_flag = !m_release_flag[i].local_release_flag;
		}
	}

	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " will unlock the set local flag" << std::endl;
		}
	}
	m_mutex_set_local_flag.unlock();


	bool is_last_thread=false;

	m_mutex_counter_lock.lock();

	m_still_waiting_for.store(m_still_waiting_for.load()-1);
	if(m_still_waiting_for.load()==0)
	{
		std::cout << "release" << std::endl;
		m_release.store(!m_release.load()); //set release flag
		m_still_waiting_for.store(m_num_threads.load());
		is_last_thread=true;
	}

	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " will unlock the counter lock" << std::endl;
		}
	}
	m_mutex_counter_lock.unlock();

	if(!is_last_thread) //don't let last thread wait
	{

	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " will wait for its release" << std::endl;
		}
	}

		bool quit=false;
		while(!quit)
		{
			bool current_release_flag=m_release.load(std::memory_order_relaxed);
			std::thread::id current_thread_id=std::this_thread::get_id();
			for(int i=0; i<m_release_flag.size(); i++)
			{
				if(m_release_flag[i].thread_id==current_thread_id)
				{
		//				std::cout << m_release_flag[i].local_release_flag << std::endl;
		//				std::cout << m_release.load() << std::endl << std::endl;
					if(m_release_flag[i].local_release_flag!=current_release_flag)
					{
						quit=true;
						//std::cout << "thread: " << i << " ended its task" << std::endl;
					}
				}
			}

/*			//if each thread is waiting release all of them
			std::vector<bool> anti_deadlock;
			for(int i=0; i<m_release_flag.size(); i++)
			{
				if(m_release_flag[i].local_release_flag==current_release_flag)
				{
					anti_deadlock.push_back(current_release_flag);
				}
				else
				{
					anti_deadlock.push_back(!current_release_flag);
				}
			}
			bool all_locked=true;
			for(int i=0; i<m_release_flag.size(); i++)
			{
				if(anti_deadlock[i]!=current_release_flag)
				{
					all_locked=false;
				}
			}
			if(all_locked==true)
			{
				for(int i=0; i<m_release_flag.size(); i++)
				{
					m_release_flag[i].local_release_flag= !current_release_flag;
				}
			}
*/
		}

	}

	for(int i=0; i<m_release_flag.size(); i++)
	{
		if(m_release_flag[i].thread_id==std::this_thread::get_id())
		{
			std::cout << "thread " << i << " will continue its regular business" << std::endl << std::endl;
		}
	}

}
