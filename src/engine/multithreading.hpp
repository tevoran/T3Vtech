#pragma once

#include <te.hpp>


namespace t3v
{
	namespace thread
	{
		class barrier
		{
		private:
			struct local_release
			{
				std::thread::id thread_id;
				bool local_release_flag;
			};

			std::mutex m_mutex_register_thread;
			std::vector<local_release> m_release_flag;

			std::mutex m_mutex_set_local_flag;
			std::mutex m_mutex_counter_lock;


			std::mutex m_mutex_setup;
			std::mutex m_mutex_release;
			std::atomic<uint32_t> m_num_threads;
			std::atomic<uint32_t> m_still_waiting_for;
			std::atomic<uint32_t> m_already_released;
			std::atomic<bool> m_release;
		public:
			barrier(const uint32_t num_threads);
			void arrive_and_wait();
		};
	}
}