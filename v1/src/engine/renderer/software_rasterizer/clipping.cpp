#include <te.hpp>

#define TE_SOFTWARE_RENDERER_W_BORDER_MIN -0.001
#define TE_SOFTWARE_RENDERER_W_BORDER_MAX 0.001

namespace t3v
{
	namespace software_rasterizer_helper
	{
			glm::vec4 clip_to_ndc_conversion(glm::vec4 in)
			{
				glm::vec4 out;
				out.x=in.x/in.w;
				out.y=in.y/in.w;
				out.z=2-in.z/in.w; //aligning projection matrix to the software renderers coordinates
				out.w=in.w;
				return out;
			}

			glm::vec4 ndc_to_clip_conversion(glm::vec4 in)
			{
				glm::vec4 out;
				out.x=in.x*in.w;
				out.y=in.y*in.w;
				out.z=(-in.z+2)*in.w;
				out.w=in.w;
				return out;
			}

			float clip_to_ndc_conversion_z(float in, float w)
			{
				return 2-in/w; //aligning projection matrix to the software renderers coordinates
			}

			float ndc_to_clip_conversion_z(float in, float w)
			{
				return (-in+2)*w;
			}
	}
}


void t3v::software_rasterizer::clipping_new(
	t3v::vertex& vertex1,
	t3v::vertex& vertex2,
	t3v::vertex& vertex3, 
	bool& clip_add_vertices,
	t3v::vertex& clip_tri_vert1,
	t3v::vertex& clip_tri_vert2,
	t3v::vertex& clip_tri_vert3)
{
	float clip_w=m_near_z_clip*(-2.001);

	int num_clipped_vertices=0;
	bool vertex1_is_clipped=false;
	bool vertex2_is_clipped=false;
	bool vertex3_is_clipped=false;

	//check the number of clipped vertices
	if(vertex1.pos.w>clip_w)
	{
		num_clipped_vertices++;
		vertex1_is_clipped=true;
	}
	if(vertex2.pos.w>clip_w)
	{
		num_clipped_vertices++;
		vertex2_is_clipped=true;
	}
	if(vertex3.pos.w>clip_w)
	{
		num_clipped_vertices++;
		vertex3_is_clipped=true;
	}

	//if one vertex needs to be clipped
	if(num_clipped_vertices==1)
	{
		//tell the caller of the function that a clipping triangle is created
		clip_add_vertices=true;

		t3v::vertex *vertex_clip1=NULL;
		t3v::vertex *vertex_non_clipped1=NULL;
		t3v::vertex *vertex_non_clipped2=NULL;

		clip_tri_vert1.texture=vertex1.texture;
		clip_tri_vert2.texture=vertex1.texture;
		clip_tri_vert3.texture=vertex1.texture;

		//determining which vertex is clipped
		if(vertex1_is_clipped==true)
		{
			vertex_clip1=&vertex1;
			vertex_non_clipped1=&vertex2;
			vertex_non_clipped2=&vertex3;
		}
		if(vertex2_is_clipped==true)
		{
			vertex_clip1=&vertex2;
			vertex_non_clipped1=&vertex1;
			vertex_non_clipped2=&vertex3;
		}
		if(vertex3_is_clipped==true)
		{
			vertex_clip1=&vertex3;
			vertex_non_clipped1=&vertex1;
			vertex_non_clipped2=&vertex2;
		}

		//do the clipping
		//first clipping vertex
		float k1 = (clip_w - vertex_clip1->pos.w)/(vertex_non_clipped1->pos.w - vertex_clip1->pos.w);

		clip_tri_vert1.pos.x = k1 * (vertex_non_clipped1->pos.x - vertex_clip1->pos.x) + vertex_clip1->pos.x;
		clip_tri_vert1.pos.y = k1 * (vertex_non_clipped1->pos.y - vertex_clip1->pos.y) + vertex_clip1->pos.y;
		clip_tri_vert1.pos.z = k1 * (vertex_non_clipped1->pos.z - vertex_clip1->pos.z) + vertex_clip1->pos.z;
		clip_tri_vert1.pos.w = clip_w;

		clip_tri_vert1.tex.u = k1 * (vertex_non_clipped1->tex.u - vertex_clip1->tex.u) + vertex_clip1->tex.u;
		clip_tri_vert1.tex.v = k1 * (vertex_non_clipped1->tex.v - vertex_clip1->tex.v) + vertex_clip1->tex.v;

		//second clipping vertex
		float k2 = (clip_w - vertex_clip1->pos.w)/(vertex_non_clipped2->pos.w - vertex_clip1->pos.w);

		clip_tri_vert2.pos.x = k2 * (vertex_non_clipped2->pos.x - vertex_clip1->pos.x) + vertex_clip1->pos.x;
		clip_tri_vert2.pos.y = k2 * (vertex_non_clipped2->pos.y - vertex_clip1->pos.y) + vertex_clip1->pos.y;
		clip_tri_vert2.pos.z = k2 * (vertex_non_clipped2->pos.z - vertex_clip1->pos.z) + vertex_clip1->pos.z;
		clip_tri_vert2.pos.w = clip_w;

		clip_tri_vert2.tex.u = k2 * (vertex_non_clipped2->tex.u - vertex_clip1->tex.u) + vertex_clip1->tex.u;
		clip_tri_vert2.tex.v = k2 * (vertex_non_clipped2->tex.v - vertex_clip1->tex.v) + vertex_clip1->tex.v;

		//making the resulting quad
		*vertex_clip1=clip_tri_vert1; //first tri -- only one vertex has to move

		clip_tri_vert3=*vertex_non_clipped2; //second tri -- only vertex left

		return;
	}

	//if two vertices need to be clipped
	if(num_clipped_vertices==2)
	{
		//determining the clipped vertices
		t3v::vertex *vertex_clip1=NULL;
		t3v::vertex *vertex_clip2=NULL;
		t3v::vertex *vertex_non_clipped=NULL;

		if(vertex1_is_clipped==false)
		{
			vertex_clip1=&vertex2;
			vertex_clip2=&vertex3;
			vertex_non_clipped=&vertex1;
		}

		if(vertex2_is_clipped==false)
		{
			vertex_clip1=&vertex1;
			vertex_clip2=&vertex3;
			vertex_non_clipped=&vertex2;
		}

		if(vertex3_is_clipped==false)
		{
			vertex_clip1=&vertex1;
			vertex_clip2=&vertex2;
			vertex_non_clipped=&vertex3;
		}

		//clip vertices
		//first vertex
		float k1 = (clip_w - vertex_clip1->pos.w)/(vertex_non_clipped->pos.w - vertex_clip1->pos.w);

		t3v::vertex tmp_vertex;
		tmp_vertex.pos.w=clip_w;
		tmp_vertex.texture=vertex1.texture;

		tmp_vertex.pos.x = k1 * (vertex_non_clipped->pos.x - vertex_clip1->pos.x) + vertex_clip1->pos.x;
		tmp_vertex.pos.y = k1 * (vertex_non_clipped->pos.y - vertex_clip1->pos.y) + vertex_clip1->pos.y;
		tmp_vertex.pos.z = k1 * (vertex_non_clipped->pos.z - vertex_clip1->pos.z) + vertex_clip1->pos.z;

		tmp_vertex.tex.u = k1 * (vertex_non_clipped->tex.u - vertex_clip1->tex.u) + vertex_clip1->tex.u;
		tmp_vertex.tex.v = k1 * (vertex_non_clipped->tex.v - vertex_clip1->tex.v) + vertex_clip1->tex.v;

		*vertex_clip1=tmp_vertex;

		//first vertex
		float k2 = (clip_w - vertex_clip2->pos.w)/(vertex_non_clipped->pos.w - vertex_clip2->pos.w);

		tmp_vertex.pos.x = k2 * (vertex_non_clipped->pos.x - vertex_clip2->pos.x) + vertex_clip2->pos.x;
		tmp_vertex.pos.y = k2 * (vertex_non_clipped->pos.y - vertex_clip2->pos.y) + vertex_clip2->pos.y;
		tmp_vertex.pos.z = k2 * (vertex_non_clipped->pos.z - vertex_clip2->pos.z) + vertex_clip2->pos.z;

		tmp_vertex.tex.u = k2 * (vertex_non_clipped->tex.u - vertex_clip2->tex.u) + vertex_clip2->tex.u;
		tmp_vertex.tex.v = k2 * (vertex_non_clipped->tex.v - vertex_clip2->tex.v) + vertex_clip2->tex.v;

		*vertex_clip2=tmp_vertex;

		return;
	}
}