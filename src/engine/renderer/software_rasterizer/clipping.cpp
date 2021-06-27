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

//clipping is only done for the near z-plane
t3v::software_rasterizer::clipping_vertices t3v::software_rasterizer::clipping(t3v::vertex& vertex1, t3v::vertex& vertex2, t3v::vertex& vertex3)
{
	using namespace t3v::software_rasterizer_helper;

	t3v::software_rasterizer::clipping_vertices clipped_vertices;

	//avoiding division by zero
	if(	vertex1.pos.w > TE_SOFTWARE_RENDERER_W_BORDER_MIN &&
		vertex1.pos.w < TE_SOFTWARE_RENDERER_W_BORDER_MAX)
	{
		vertex1.pos.w=TE_SOFTWARE_RENDERER_W_BORDER_MIN;
	}
	if(	vertex2.pos.w > TE_SOFTWARE_RENDERER_W_BORDER_MIN &&
		vertex2.pos.w < TE_SOFTWARE_RENDERER_W_BORDER_MAX)
	{
		vertex2.pos.w=TE_SOFTWARE_RENDERER_W_BORDER_MIN;	
	}
	if(	vertex3.pos.w > TE_SOFTWARE_RENDERER_W_BORDER_MIN &&
		vertex3.pos.w < TE_SOFTWARE_RENDERER_W_BORDER_MAX)
	{
		vertex3.pos.w=TE_SOFTWARE_RENDERER_W_BORDER_MIN;
	}

	//determining whether it's necessary to clip with the near z plane
	if(	clip_to_ndc_conversion_z(vertex1.pos.z, vertex1.pos.w) < 0 || 
		clip_to_ndc_conversion_z(vertex2.pos.z, vertex2.pos.w) < 0 ||
		clip_to_ndc_conversion_z(vertex3.pos.z, vertex3.pos.w) < 0 ||
		(vertex1.pos.z>0 && vertex1.pos.w>0) ||
		(vertex2.pos.z>0 && vertex2.pos.w>0) ||
		(vertex3.pos.z>0 && vertex3.pos.w>0) )
	{
		std::vector<t3v::vertex> list_of_vertices; //necessary for setting up the final configuration of vertices

		//there are always 2 intersection points with the clipping plane
		t3v::vertex intersection1;
			intersection1.pos={0, 0, -m_near_z_clip, -1};
			intersection1.texture=vertex1.texture;

		t3v::vertex intersection2;
			intersection2.pos={0, 0, -m_near_z_clip, -1};
			intersection2.texture=vertex1.texture;

		//determining the edges of the triangle that are going through the clipping plane
		//if equal the vertices don't go through the plane
		list_of_vertices.push_back(vertex1);
		if(vertex1.pos.z!=vertex2.pos.z)
		{
			float k = (m_near_z_clip-vertex1.pos.z)/(vertex2.pos.z-vertex1.pos.z);

			if(k>0 && k<1) //intersection needs to be between the vertices
			{
				intersection1.pos.x = k*(vertex2.pos.x-vertex1.pos.x) + vertex1.pos.x;
				intersection1.pos.y = k*(vertex2.pos.y-vertex1.pos.y) + vertex1.pos.y;

				intersection1.pos.w = k*(vertex2.pos.w-vertex1.pos.w) + vertex1.pos.w;

				intersection1.tex.u= k*(vertex2.tex.u-vertex1.tex.u) + vertex1.tex.u;
				intersection1.tex.v = k*(vertex2.tex.v-vertex1.tex.v) + vertex1.tex.v;

				if(intersection1.pos.w>0)
				{
					intersection1.pos.w=-intersection1.pos.w;					
				}
				list_of_vertices.push_back(intersection1);
			}
		}

		list_of_vertices.push_back(vertex2);
		if(vertex2.pos.z!=vertex3.pos.z)
		{
			float k = (m_near_z_clip-vertex2.pos.z)/(vertex3.pos.z-vertex2.pos.z);

			if(k>0 && k<1) //intersection needs to be between the vertices
			{
				if(intersection1.pos.x==0 && intersection1.pos.y==0)
				{
					intersection1.pos.x = k*(vertex3.pos.x-vertex2.pos.x) + vertex2.pos.x;
					intersection1.pos.y = k*(vertex3.pos.y-vertex2.pos.y) + vertex2.pos.y;

					intersection1.pos.w = k*(vertex3.pos.w-vertex2.pos.w) + vertex2.pos.w;

					intersection1.tex.u= k*(vertex3.tex.u-vertex2.tex.u) + vertex2.tex.u;
					intersection1.tex.v = k*(vertex3.tex.v-vertex2.tex.v) + vertex2.tex.v;

					if(intersection1.pos.w>0)
					{
						intersection1.pos.w=-intersection1.pos.w;
					}
					list_of_vertices.push_back(intersection1);
				}
				else
				{
					intersection2.pos.x = k*(vertex3.pos.x-vertex2.pos.x) + vertex2.pos.x;
					intersection2.pos.y = k*(vertex3.pos.y-vertex2.pos.y) + vertex2.pos.y;

					intersection2.pos.w = k*(vertex3.pos.w-vertex2.pos.w) + vertex2.pos.w;

					intersection2.tex.u= k*(vertex3.tex.u-vertex2.tex.u) + vertex2.tex.u;
					intersection2.tex.v = k*(vertex3.tex.v-vertex2.tex.v) + vertex2.tex.v;
					if(intersection2.pos.w>0)
					{
						intersection2.pos.w=-intersection2.pos.w;
					}
					list_of_vertices.push_back(intersection2);
				}
			}
		}

		list_of_vertices.push_back(vertex3);
		if(vertex3.pos.z!=vertex1.pos.z)
		{
			float k = (m_near_z_clip-vertex3.pos.z)/(vertex1.pos.z-vertex3.pos.z);

			if(k>0 && k<1) //intersection needs to be between the vertices
			{
				if(intersection1.pos.x==0 && intersection1.pos.y==0)
				{
					intersection1.pos.x = k*(vertex1.pos.x-vertex3.pos.x) + vertex3.pos.x;
					intersection1.pos.y = k*(vertex1.pos.y-vertex3.pos.y) + vertex3.pos.y;

					intersection1.pos.w = k*(vertex1.pos.w-vertex3.pos.w) + vertex3.pos.w;

					intersection1.tex.u= k*(vertex1.tex.u-vertex3.tex.u) + vertex3.tex.u;
					intersection1.tex.v = k*(vertex1.tex.v-vertex3.tex.v) + vertex3.tex.v;

					if(intersection1.pos.w>0)
					{
						intersection1.pos.w=-intersection1.pos.w;
					}
					list_of_vertices.push_back(intersection1);
				}
				else
				{
					intersection2.pos.x = k*(vertex1.pos.x-vertex3.pos.x) + vertex3.pos.x;
					intersection2.pos.y = k*(vertex1.pos.y-vertex3.pos.y) + vertex3.pos.y;

					intersection2.pos.w = k*(vertex1.pos.w-vertex3.pos.w) + vertex3.pos.w;

					intersection2.tex.u= k*(vertex1.tex.u-vertex3.tex.u) + vertex3.tex.u;
					intersection2.tex.v = k*(vertex1.tex.v-vertex3.tex.v) + vertex3.tex.v;

					if(intersection2.pos.w>0)
					{
						intersection2.pos.w=-intersection2.pos.w;
					}
					list_of_vertices.push_back(intersection2);
				}
			}
		}

		//calculating the number of necessary vertices
		//and using the right vertices that are not behind the plane
		int i_clipped_tmp=0;
		t3v::vertex clipped_vertices_tmp[4];
		for(int i=0; i<list_of_vertices.size(); i++)
		{
			if(list_of_vertices[i].pos.z<=0)
			{
				clipped_vertices_tmp[i_clipped_tmp]=list_of_vertices[i];

				i_clipped_tmp++;
			}
		}

		//building the one or two triangles
		if(i_clipped_tmp==3) //one triangle
		{
			clipped_vertices.num_vertices=3;
			clipped_vertices.vertex[0]=clipped_vertices_tmp[0];
			clipped_vertices.vertex[1]=clipped_vertices_tmp[1];
			clipped_vertices.vertex[2]=clipped_vertices_tmp[2];
		}

		if(i_clipped_tmp==4) //two triangles
		{
			clipped_vertices.num_vertices=6;
			clipped_vertices.vertex[0]=clipped_vertices_tmp[0];
			clipped_vertices.vertex[1]=clipped_vertices_tmp[1];
			clipped_vertices.vertex[2]=clipped_vertices_tmp[2];

			clipped_vertices.vertex[3]=clipped_vertices_tmp[0];
			clipped_vertices.vertex[4]=clipped_vertices_tmp[2];
			clipped_vertices.vertex[5]=clipped_vertices_tmp[3];
		}

		list_of_vertices.erase(list_of_vertices.begin(), list_of_vertices.end());
	}
	else
	{
		clipped_vertices.num_vertices=3;
		clipped_vertices.vertex[0]=vertex1;
		clipped_vertices.vertex[1]=vertex2;
		clipped_vertices.vertex[2]=vertex3;
	}

	return clipped_vertices;
}