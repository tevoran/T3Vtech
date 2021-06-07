#include <te.hpp>

t3v::vertex t3v::perspective_divide(t3v::vertex& vertex_in)
{
	t3v::vertex vertex_out;
	float z=1/vertex_in.pos.z;
	vertex_out.pos=vertex_in.pos/vertex_in.pos.z;

	return vertex_out;
}