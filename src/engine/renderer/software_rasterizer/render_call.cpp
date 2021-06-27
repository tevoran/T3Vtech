#include <te.hpp>

void t3v::software_rasterizer::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale)
{
	//writing to rendering vertex buffer
	for(int i=0; i<num_vertices/3; i++)
	{
		//adding texture
		t3v::vertex vertex1 = vertices[i*3];
			vertex1.texture=texture;
		t3v::vertex vertex2 = vertices[i*3+1];
			vertex2.texture=texture;
		t3v::vertex vertex3 = vertices[i*3+2];
			vertex3.texture=texture;


		//applying vertexshader
		vertex_shader(vertex1, pos, rotation_mat, scale);
		vertex_shader(vertex2, pos, rotation_mat, scale);
		vertex_shader(vertex3, pos, rotation_mat, scale);

/*
		std::cout << "Vertex 1: pre" << std::endl;
		std::cout << vertex1.pos.x << std::endl;
		std::cout << vertex1.pos.y << std::endl;
		std::cout << vertex1.pos.z << std::endl;
		std::cout << vertex1.pos.w << std::endl << std::endl;

		std::cout << "Vertex 2: pre" << std::endl;
		std::cout << vertex2.pos.x << std::endl;
		std::cout << vertex2.pos.y << std::endl;
		std::cout << vertex2.pos.z << std::endl;
		std::cout << vertex2.pos.w << std::endl << std::endl;

		std::cout << "Vertex 3: pre" << std::endl;
		std::cout << vertex3.pos.x << std::endl;
		std::cout << vertex3.pos.y << std::endl;
		std::cout << vertex3.pos.z << std::endl;
		std::cout << vertex3.pos.w << std::endl << std::endl << std::endl;
*/

		//drop triangle if it's completely behind the near-z clipping plane
		if(	vertex1.pos.z > -m_near_z_clip &&
			vertex2.pos.z > -m_near_z_clip &&
			vertex3.pos.z > -m_near_z_clip)
		{
			continue;
		}

		//clipping
		t3v::software_rasterizer::clipping_vertices clipped_vertices=clipping(vertex1, vertex2, vertex3);
//		std::cout << clipped_vertices.num_vertices << std::endl;

		//perspective divide
		for(int i=0; i<clipped_vertices.num_vertices; i++)
		{
//			std::cout << clipped_vertices.vertex[i].pos.x << std::endl;
//			std::cout << clipped_vertices.vertex[i].pos.y << std::endl;
//			std::cout << clipped_vertices.vertex[i].pos.z << std::endl;
//			std::cout << clipped_vertices.vertex[i].pos.w << std::endl << std::endl;

			perspective_divide(clipped_vertices.vertex[i]);
		}

		for(int i=0; i<clipped_vertices.num_vertices; i=i+3) //looping through complete triangles
		{
			//sorting vertices along y-axis
			if(clipped_vertices.vertex[i].pos.y > clipped_vertices.vertex[i+1].pos.y)
			{
				std::swap(clipped_vertices.vertex[i], clipped_vertices.vertex[i+1]);
			}
			if(clipped_vertices.vertex[i+1].pos.y > clipped_vertices.vertex[i+2].pos.y)
			{
				std::swap(clipped_vertices.vertex[i+1], clipped_vertices.vertex[i+2]);
			}
			if(clipped_vertices.vertex[i].pos.y > clipped_vertices.vertex[i+1].pos.y)
			{
				std::swap(clipped_vertices.vertex[i], clipped_vertices.vertex[i+1]);
			}

			//putting vertices into drawing buffer
			//they are drawn when the update function is executed
			m_rendering_vertex_buffer.push_back(clipped_vertices.vertex[i]);
			m_rendering_vertex_buffer.push_back(clipped_vertices.vertex[i+1]);
			m_rendering_vertex_buffer.push_back(clipped_vertices.vertex[i+2]);
		}

/*
		std::cout << "Vertex 1: post" << std::endl;
		std::cout << vertex1.pos.x << std::endl;
		std::cout << vertex1.pos.y << std::endl;
		std::cout << vertex1.pos.z << std::endl;
		std::cout << vertex1.pos.w << std::endl << std::endl;

		std::cout << "Vertex 2: post" << std::endl;
		std::cout << vertex2.pos.x << std::endl;
		std::cout << vertex2.pos.y << std::endl;
		std::cout << vertex2.pos.z << std::endl;
		std::cout << vertex2.pos.w << std::endl << std::endl;

		std::cout << "Vertex 3: post" << std::endl;
		std::cout << vertex3.pos.x << std::endl;
		std::cout << vertex3.pos.y << std::endl;
		std::cout << vertex3.pos.z << std::endl;
		std::cout << vertex3.pos.w << std::endl << std::endl << std::endl;
*/

	}

	m_update_necessary=true;
}
