#include <te.hpp>

void t3v::software_rasterizer::render2D(SDL_Surface *surface, SDL_Rect& src_rect, SDL_Rect& dst_rect)
{
	t3v::software_rasterizer::sprite_queue_entry entry;
	entry.dst_rect=dst_rect;
	entry.src_rect=src_rect;
	entry.surface=surface;

	m_sprite_render_queue.push_back(entry);
}
