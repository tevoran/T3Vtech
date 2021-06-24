#include <te.hpp>

void t3v::software_rasterizer::vertex_shader(t3v::vertex& vertex, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale)
{
	vertex.pos.x=vertex.pos.x*scale.x;
	vertex.pos.y=vertex.pos.y*scale.y;
	vertex.pos.z=vertex.pos.z*scale.z;
	
	glm::vec4 vertex4 = rotation_mat * vertex.pos;
	vertex4 = vertex4 + glm::vec4(-pos.x, -pos.y, pos.z , 0.0);
	vertex4 = m_projection_mat * vertex4;

	vertex.pos = vertex4;
}