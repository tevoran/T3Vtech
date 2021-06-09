#include <te.hpp>


t3v::object3d::object3d()
{
}

t3v::object3d::~object3d()
{
	
}

void t3v::object3d::use_vertices(t3v::vertex *vertices_in, const int num_vertices)
{
	m_vertices=vertices_in;
	m_num_vertices=num_vertices;
}

void t3v::object3d::use_texture(t3v::texture *texture_in)
{
	m_texture=texture_in;
}

void t3v::object3d::render()
{
	t3v::engine& te=t3v::engine::get();
	te.render(m_vertices, m_num_vertices, m_texture);
}