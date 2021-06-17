#include <te.hpp>


t3v::object3d::object3d()
{
	m_current_rotation=glm::mat4(1.0f); //initializing rotation matrix
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

void t3v::object3d::rotate(glm::vec3 axis, float rotation_degrees)
{
	m_current_rotation=rotation_quaternion(m_current_rotation, axis, rotation_degrees);
}

void t3v::object3d::render()
{
	t3v::engine& te=t3v::engine::get();
	te.render(m_vertices, m_num_vertices, m_texture, m_pos, m_current_rotation, m_scale);
}

void t3v::object3d::position(glm::vec3 position)
{
	m_pos=position;
}

void t3v::object3d::scale(float scale)
{
	m_scale=glm::vec3(scale, scale, scale);
}

void t3v::object3d::scale(glm::vec3 scale)
{
	m_scale=scale;
}