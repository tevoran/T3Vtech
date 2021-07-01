#pragma once
#include <te.hpp>



namespace t3v
{
	//font
	//it is possible to use font sizes between 6pt and 108pt
	class font
	{
	public:
		TTF_Font *font_size[TE_FONT_MAX_SIZE-TE_FONT_MIN_SIZE+1];

		font(const char *path);
		~font();
	};

	//sprite
	class sprite
	{
	public:
		SDL_Surface *surface=NULL;
		sprite(const char *path);
		~sprite();
	};

	//texture handling
	t3v::texture* load_texture(const char *path);
	void free_texture(t3v::texture *texture);
}

 