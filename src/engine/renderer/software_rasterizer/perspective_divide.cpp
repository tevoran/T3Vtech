#include <te.hpp>

void t3v::software_rasterizer::perspective_divide(t3v::vertex& vertex)
{
		vertex.pos.x=vertex.pos.x/vertex.pos.w;
		vertex.pos.y=vertex.pos.y/vertex.pos.w;
		vertex.pos.z=2-vertex.pos.z/vertex.pos.w; //aligning projection matrix to the software renderers coordinates

		//texture coordinates
		vertex.tex.u=vertex.tex.u/vertex.pos.w;
		vertex.tex.v=vertex.tex.v/vertex.pos.w;

		vertex.pos=glm::vec4(vertex.pos.x+0.5, -vertex.pos.y+0.5, vertex.pos.z, 1/vertex.pos.w); //0.5 for having nicer aligned axes
}