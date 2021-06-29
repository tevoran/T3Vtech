#pragma once

#include <te.hpp>


namespace t3v
{
	namespace thread
	{
		class barrier
		{
		private:
			int m_num_threads;
			int m_count;
			volatile bool m_release;
			std::mutex m_mutex;
		public:
			barrier(const uint32_t num_threads);
			bool arrive();
			void wait(bool arrival_token);
			void arrive_and_wait();
		};
	}
}