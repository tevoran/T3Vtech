#include <te.hpp>

void t3v::software_rasterizer::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat)
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
		vertex_shader(vertex1, pos, rotation_mat);
		vertex_shader(vertex2, pos, rotation_mat);
		vertex_shader(vertex3, pos, rotation_mat);


		//don't draw negative only z-stuff
		if(vertex1.pos.z<0 && vertex2.pos.z<0 && vertex3.pos.z<0)
		{
			continue;
		}

		//don't draw stuff beyound far clipping plane
		if(vertex1.pos.z>1 && vertex2.pos.z>1 && vertex3.pos.z>1)
		{
			continue;
		}

		//sorting vertices along y-axis
		if(vertex1.pos.y > vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}
		if(vertex2.pos.y > vertex3.pos.y)
		{
			std::swap(vertex2, vertex3);
		}
		if(vertex1.pos.y > vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}

		//putting vertices into drawing buffer
		//they are drawn when the update function is executed
		m_rendering_vertex_buffer.push_back(vertex1);
		m_rendering_vertex_buffer.push_back(vertex2);
		m_rendering_vertex_buffer.push_back(vertex3);
	}

	m_update_necessary=true;
}
