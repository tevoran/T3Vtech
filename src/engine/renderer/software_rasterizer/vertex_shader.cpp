#include <te.hpp>

void t3v::software_rasterizer::vertex_shader(t3v::vertex& vertex, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale)
{


	vertex.pos.x=vertex.pos.x*scale.x;
	vertex.pos.y=vertex.pos.y*scale.y;
	vertex.pos.z=vertex.pos.z*scale.z;
	
	glm::vec4 vertex4 = rotation_mat * vertex.pos;
	vertex4 = vertex4 + glm::vec4(pos, 0.0);
	vertex4 = m_projection_mat * vertex4;



	//perspective divide
	vertex4.x=vertex4.x/vertex4.w;
	vertex4.y=vertex4.y/vertex4.w;
	vertex4.z=2-vertex4.z/vertex4.w; //aligning projection matrix to the software renderers coordinates

	//texture coordinates
	vertex.tex.u=vertex.tex.u/vertex4.w;
	vertex.tex.v=vertex.tex.v/vertex4.w;


	vertex.pos=glm::vec4(vertex4.x+0.5, -vertex4.y+0.5, vertex4.z, 1/vertex4.w); //0.5 for having nicer aligned axes

}