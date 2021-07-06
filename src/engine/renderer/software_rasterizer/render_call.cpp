#include <te.hpp>

void t3v::software_rasterizer::render(t3v::vertex *vertices, const int num_vertices, t3v::texture *texture, glm::vec3& pos, glm::mat4& rotation_mat, glm::vec3& scale)
{
	//temporary vertices if an additional clipping triangle is created
	t3v::vertex clip_tri_vert1;
	t3v::vertex clip_tri_vert2;
	t3v::vertex clip_tri_vert3;

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


		//clipping against the z-near-plane
		//if three vertices are behind the clipping plane then drop them
		float clip_w=m_near_z_clip*(-2.001);
		if(	vertex1.pos.w>clip_w &&
			vertex2.pos.w>clip_w &&
			vertex3.pos.w>clip_w)
		{
			continue;
		}

		bool clip_tri_is_created=false;
		clipping_new(
			vertex1,
			vertex2,
			vertex3,
			clip_tri_is_created,
			clip_tri_vert1,
			clip_tri_vert2,
			clip_tri_vert3);

		perspective_divide(vertex1);
		perspective_divide(vertex2);
		perspective_divide(vertex3);

		//sorting the vertices along the y-axis
		if(vertex1.pos.y>vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}
		if(vertex2.pos.y>vertex3.pos.y)
		{
			std::swap(vertex2, vertex3);
		}
		if(vertex1.pos.y>vertex2.pos.y)
		{
			std::swap(vertex1, vertex2);
		}

		//putting the vertices into the render buffer
		m_rendering_vertex_buffer.push_back(vertex1);
		m_rendering_vertex_buffer.push_back(vertex2);
		m_rendering_vertex_buffer.push_back(vertex3);

		if(clip_tri_is_created==true)
		{
			perspective_divide(clip_tri_vert1);
			perspective_divide(clip_tri_vert2);
			perspective_divide(clip_tri_vert3);


			//sorting the vertices along the y-axis
			if(clip_tri_vert1.pos.y>clip_tri_vert2.pos.y)
			{
				std::swap(clip_tri_vert1, clip_tri_vert2);
			}
			if(clip_tri_vert2.pos.y>clip_tri_vert3.pos.y)
			{
				std::swap(clip_tri_vert2, clip_tri_vert3);
			}
			if(clip_tri_vert1.pos.y>clip_tri_vert2.pos.y)
			{
				std::swap(clip_tri_vert1, clip_tri_vert2);
			}

			//putting the vertices into the render buffer
			m_rendering_vertex_buffer.push_back(clip_tri_vert1);
			m_rendering_vertex_buffer.push_back(clip_tri_vert2);
			m_rendering_vertex_buffer.push_back(clip_tri_vert3);
		}
	}

	m_update_necessary=true;
}
