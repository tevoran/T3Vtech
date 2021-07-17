#include <te.hpp>

void t3v::object3d::make_quad(float width, float height) //creating quad primitive
{
	m_data_type=TE_OBJECT3D_QUAD;
	
	m_num_vertices=6; //a quad needs 6 vertices

	t3v::vertex *vertices = new t3v::vertex[m_num_vertices];
	m_vertices = vertices;

	//first triangle
	//first vertex
	vertices[0].pos.x=-0.5*width;
	vertices[0].pos.y=0.5*height;

	vertices[0].tex.u=1;
	vertices[0].tex.v=1;

	//second vertex
	vertices[1].pos.x=0.5*width;
	vertices[1].pos.y=0.5*height;

	vertices[1].tex.u=0;
	vertices[1].tex.v=1;

	//third vertex
	vertices[2].pos.x=-0.5*width;
	vertices[2].pos.y=-0.5*height;

	vertices[2].tex.u=1;
	vertices[2].tex.v=0;


	//second triangle
	//first vertex
	vertices[3].pos.x=0.5*width;
	vertices[3].pos.y=0.5*height;

	vertices[3].tex.u=0;
	vertices[3].tex.v=1;

	//second vertex
	vertices[4].pos.x=0.5*width;
	vertices[4].pos.y=-0.5*height;

	vertices[4].tex.u=0;
	vertices[4].tex.v=0;

	//third vertex
	vertices[5].pos.x=-0.5*width;
	vertices[5].pos.y=-0.5*height;

	vertices[5].tex.u=1;
	vertices[5].tex.v=0;
}