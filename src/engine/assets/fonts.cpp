#include <te.hpp>

t3v::font::font(const char *path)
{
	for(int i=TE_FONT_MIN_SIZE; i<=(TE_FONT_MAX_SIZE); i++)
	{
		font_size[i-TE_FONT_MIN_SIZE]=TTF_OpenFont(path, i);
		if(font_size[i-TE_FONT_MIN_SIZE]==NULL)
		{
			std::cout << "[ERROR] error while reading font from \"" << path << "\"" << std::endl;
			std::cout << "SDL2_ttf error message: " << std::endl;
			std::cout << TTF_GetError() << std::endl;
			exit(0);
		} 
	}
	std::cout << "Font successfully loaded" << std::endl;
}

t3v::font::~font()
{
	for(int i=TE_FONT_MIN_SIZE; i<=TE_FONT_MAX_SIZE; i++)
	{
		TTF_CloseFont(font_size[i-TE_FONT_MIN_SIZE]);
	}
}