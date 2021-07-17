#include <te.hpp>


void t3v::software_rasterizer::print_single_frame(std::string text, t3v::font& font, t3v::color color_in, int font_size, int x, int y)
{
	if(font_size>=TE_FONT_MIN_SIZE && font_size<=TE_FONT_MAX_SIZE)
	{
		t3v::software_rasterizer::text_queue_entry tmp_text;
		SDL_Color color={color_in.b, color_in.g, color_in.r, color_in.a};
		tmp_text.text_surface = TTF_RenderText_Solid(font.font_size[font_size-TE_FONT_MIN_SIZE], text.c_str(), color);
		tmp_text.dst_rect.w=tmp_text.text_surface->w;
		tmp_text.dst_rect.h=tmp_text.text_surface->h;
		tmp_text.dst_rect.x=x;
		tmp_text.dst_rect.y=y;

		m_text_single_frame_queue.push_back(tmp_text);
	}
	else
	{
		std::cout << "[ERROR] font size is beyond the allowed limit of " <<
		TE_FONT_MIN_SIZE << " and " << TE_FONT_MAX_SIZE  << "pt" << std::endl;
	}
}
