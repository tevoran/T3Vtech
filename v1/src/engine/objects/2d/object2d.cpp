#include <te.hpp>

t3v::object2d::object2d()
{

}

t3v::object2d::~object2d()
{
}

void t3v::object2d::use_sprite(t3v::sprite& sprite)
{
	m_surface=sprite.surface;

	m_dst_rect.w=m_surface->w;
	m_dst_rect.h=m_surface->h;

	m_src_rect.x=0;
	m_src_rect.y=0;
	m_src_rect.w=m_dst_rect.w;
	m_src_rect.h=m_dst_rect.h;
}

void t3v::object2d::position(const int x, const int y)
{
	m_dst_rect.x=x;
	m_dst_rect.y=y;
}

void t3v::object2d::scale(const float scale)
{
	m_dst_rect.w=(float)m_src_rect.w*scale;
	m_dst_rect.h=(float)m_src_rect.h*scale;
}


void t3v::object2d::render()
{
	if(m_surface==NULL)
	{
		std::cout << "[ERROR] can't render this object2d because no sprite has been loaded" << std::endl;
	}
	//render
	else
	{
		t3v::engine& te=t3v::engine::get();
		te.render2D(m_surface, m_src_rect, m_dst_rect);
	}
}