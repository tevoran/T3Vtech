#include <te.hpp>



t3v::texture* t3v::load_texture(const char *path)
{
	t3v::texture *texture=new t3v::texture;

	SDL_Surface *tmp_surface=IMG_Load(path);
	//success
	if(tmp_surface!=NULL)
	{
		std::cout << "[DONE] texture \"" << path << "\" successfully loaded" << std::endl;
	}
	//error
	else
	{
		std::cout << "[ERROR] couldn't load texture from: \"" << path << "\" " << std::endl <<
		"The asset might be missing or SDL2_image might have an issue." << std::endl;
	}

	//getting data from SDL_Surface to the engine texture format
	texture->w=tmp_surface->w;
	texture->h=tmp_surface->h;
	uint8_t *data=new uint8_t[texture->w*texture->h*TE_COLORDEPTH]; //colordepth is 4 bytes
	switch(tmp_surface->format->format)
	{
		case SDL_PIXELFORMAT_BGR24:
		{
			uint8_t *in=(uint8_t*)tmp_surface->pixels;
			uint8_t *data_write=data;
			for(int i=0; i<(texture->w*texture->h*TE_COLORDEPTH); i+=TE_COLORDEPTH)
			{
				*data_write=*(in+2); //R-value
				data_write++;
				*data_write=*(in+1); //G-value
				data_write++;
				*data_write=*(in); //B-value;
				data_write++;
				*data_write=0; //A-value
				data_write++;
				in+=3;
			}
			texture->data=(uint8_t*)data;
			break;
		}

		case SDL_PIXELFORMAT_RGB24:
		{
			uint8_t *in=(uint8_t*)tmp_surface->pixels;
			uint8_t *data_write=data;
			for(int i=0; i<(texture->w*texture->h*TE_COLORDEPTH); i+=TE_COLORDEPTH)
			{
				*data_write=*(in); //R-value
				data_write++;
				*data_write=*(in+1); //G-value
				data_write++;
				*data_write=*(in+2); //B-value;
				data_write++;
				*data_write=0; //A-value
				data_write++;
				in+=3;
			}
			texture->data=(uint8_t*)data;
			break;
		}

		default:
			std::cout << "[ERROR] pixel format from texture at : \"" << path << "\" unusable" << std::endl; 
			std::cout << "Pixel format is: " << SDL_GetPixelFormatName(tmp_surface->format->format) << std::endl;
	}


	std::cout << "width: " << texture->w << " height: " << texture->h << std::endl;
	std::cout << "[WARNING] Textures currently have to be freed manually" << std::endl;

	SDL_FreeSurface(tmp_surface);
	return texture;
}

void t3v::free_texture(t3v::texture *texture)
{
	delete [] texture->data;
	delete texture;
}