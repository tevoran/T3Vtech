#pragma once
#include <te.hpp>

namespace t3v
{
	class engine
	{
	private:
		//SDL stuff
		SDL_Window *window=NULL;


		engine();
		~engine();
	public:


		engine(const engine&) = delete;
		static engine& get()
		{
			static engine instance;
			return instance;
		}
	};
}