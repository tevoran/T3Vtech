#include <te.hpp>

void t3v::software_rasterizer::near_z_clip_double(t3v::vertex& vertex_clipped, const t3v::vertex& vertex_non_clipped)
{
	float tmp = -vertex_clipped.pos.z/(vertex_non_clipped.pos.z - vertex_clipped.pos.z);

	//clipping vertex position data
	vertex_clipped.pos.x = tmp * (vertex_non_clipped.pos.x - vertex_clipped.pos.x) + vertex_clipped.pos.x;
	vertex_clipped.pos.y = tmp * (vertex_non_clipped.pos.y - vertex_clipped.pos.y) + vertex_clipped.pos.y;
	vertex_clipped.pos.z = 0;

	//clipping texture coordinates
	vertex_clipped.tex.u = tmp * (vertex_non_clipped.tex.u - vertex_clipped.tex.u) + vertex_clipped.tex.u;
	vertex_clipped.tex.v = tmp * (vertex_non_clipped.tex.v - vertex_clipped.tex.v) + vertex_clipped.tex.v;
}


//moves clipped vertex onto clipping plane and creates a new vertex
t3v::vertex t3v::software_rasterizer::near_z_clip_single(
	t3v::vertex& vertex_clipped, 
	const t3v::vertex& vertex_non_clipped_1, 
	const t3v::vertex& vertex_non_clipped_2)
{
	t3v::vertex new_vertex=vertex_clipped;

	if(vertex_clipped.pos.y>=0)
	{
		//moving first vertex to near clipping plane
		near_z_clip_double(vertex_clipped, vertex_non_clipped_1);
		//and newly created vertex
		near_z_clip_double(new_vertex, vertex_non_clipped_2);
	}
	else
	{
		//moving first vertex to near clipping plane
		near_z_clip_double(vertex_clipped, vertex_non_clipped_2);
		//and newly created vertex
		near_z_clip_double(new_vertex, vertex_non_clipped_1);
	}


	return new_vertex;
}
