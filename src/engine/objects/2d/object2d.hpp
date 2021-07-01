#pragma once

#include <te.hpp>

namespace t3v
{
	class object2d
	{
	private:

	public:
		SDL_Surface *m_surface=NULL;
		SDL_Rect m_dst_rect;
		SDL_Rect m_src_rect;

		object2d();
		~object2d();

		void use_sprite(t3v::sprite& sprite);
		void position(const int x, const int y);
		void scale(const float scale);
		void render();
	};
}