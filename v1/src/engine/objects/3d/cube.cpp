#include <te.hpp>

namespace t3v
{
	namespace helper
	{
		void make_cube_face(
			t3v::vertex *vertices, 
			glm::vec3 left_top, 
			glm::vec3 right_top, 
			glm::vec3 left_bottom, 
			glm::vec3 right_bottom)
		{
			//first triangle
			//first vertex
			vertices[0].pos=glm::vec4(left_top, 1.0);

			vertices[0].tex.u=1;
			vertices[0].tex.v=1;

			//second vertex
			vertices[1].pos=glm::vec4(right_top, 1.0);

			vertices[1].tex.u=0;
			vertices[1].tex.v=1;

			//third vertex
			vertices[2].pos=glm::vec4(left_bottom, 1.0);

			vertices[2].tex.u=1;
			vertices[2].tex.v=0;


			//second triangle
			//first vertex
			vertices[3].pos=glm::vec4(right_top, 1.0);

			vertices[3].tex.u=0;
			vertices[3].tex.v=1;

			//second vertex
			vertices[4].pos=glm::vec4(right_bottom, 1.0);

			vertices[4].tex.u=0;
			vertices[4].tex.v=0;

			//third vertex
			vertices[5].pos=glm::vec4(left_bottom, 1.0);

			vertices[5].tex.u=1;
			vertices[5].tex.v=0;
		}
	}
}

void t3v::object3d::make_cube(float size)
{
	m_data_type=TE_OBJECT3D_CUBE;
	m_num_vertices=36;

	t3v::vertex *vertices=new t3v::vertex[m_num_vertices];
	m_vertices=vertices;

	//front face
	t3v::helper::make_cube_face(
		vertices, 
		{-0.5*size, 0.5*size, -0.5*size}, 
		{0.5*size, 0.5*size, -0.5*size}, 
		{-0.5*size, -0.5*size, -0.5*size}, 
		{0.5*size, -0.5*size, -0.5*size});

	//back face
	t3v::helper::make_cube_face(
		vertices+6, 
		{0.5*size, 0.5*size, 0.5*size}, 
		{-0.5*size, 0.5*size, 0.5*size}, 
		{0.5*size, -0.5*size, 0.5*size}, 
		{-0.5*size, -0.5*size, 0.5*size});

	//top face
	t3v::helper::make_cube_face(
		vertices+12, 
		{0.5*size, 0.5*size, -0.5*size}, 
		{-0.5*size, 0.5*size, -0.5*size}, 
		{0.5*size, 0.5*size, 0.5*size}, 
		{-0.5*size, 0.5*size, 0.5*size});

	//bottom face
	t3v::helper::make_cube_face(
		vertices+18, 
		{-0.5*size, -0.5*size, -0.5*size}, 
		{0.5*size, -0.5*size, -0.5*size}, 
		{-0.5*size, -0.5*size, 0.5*size}, 
		{0.5*size, -0.5*size, 0.5*size});

	//left face
	t3v::helper::make_cube_face(
		vertices+24, 
		{-0.5*size, 0.5*size, -0.5*size}, 
		{-0.5*size, 0.5*size, 0.5*size}, 
		{-0.5*size, -0.5*size, -0.5*size}, 
		{-0.5*size, -0.5*size, 0.5*size});

	//le face
	t3v::helper::make_cube_face(
		vertices+30, 
		{0.5*size, 0.5*size, 0.5*size}, 
		{0.5*size, 0.5*size, -0.5*size}, 
		{0.5*size, -0.5*size, 0.5*size}, 
		{0.5*size, -0.5*size, -0.5*size});
}