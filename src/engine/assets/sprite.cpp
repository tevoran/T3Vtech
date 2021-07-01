#include <te.hpp>


t3v::sprite::sprite(const char *path)
{
	surface=IMG_Load(path);
	if(surface!=NULL)
	{
		std::cout << "Sprite from " << path << " has been loaded successfully" << std::endl;
	}
	else
	{
		std::cout << "[ERROR] couldn't load sprite from " << path << std::endl;
		std::cout << "The asset might be missing or SDL2_image might have an issue." << std::endl;
	}
}

t3v::sprite::~sprite()
{

}