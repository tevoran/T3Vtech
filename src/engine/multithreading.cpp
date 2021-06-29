#include <te.hpp>

t3v::thread::barrier::barrier(const uint32_t num_threads)
{
	m_num_threads=num_threads;
	m_count=0;
	m_release=true;
}

bool t3v::thread::barrier::arrive()
{
	m_mutex.lock();
	bool arrival_token=!m_release;
	m_count++;
	std::cout << m_count << std::endl;
	if(m_count==m_num_threads)
	{	
		m_count=0;
		m_release=arrival_token;
	}
	m_mutex.unlock();

	return arrival_token;
}

void t3v::thread::barrier::wait(bool arrival_token)
{
	while(m_release==arrival_token)
	{
	}
}

void t3v::thread::barrier::arrive_and_wait()
{
	wait(arrive());
}
