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
t3v::vertex* t3v::software_rasterizer::clipping(t3v::vertex& vertex1, t3v::vertex& vertex2, t3v::vertex& vertex3)
{
	using namespace t3v::software_rasterizer_helper;

	t3v::vertex* out=NULL; //return value if no new vertices are created is NULL

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
		clip_to_ndc_conversion_z(vertex3.pos.z, vertex3.pos.w) < 0)
	{
		
		std::cout << clip_to_ndc_conversion_z(vertex1.pos.z, vertex1.pos.w) << std::endl;
		std::cout << clip_to_ndc_conversion_z(vertex2.pos.z, vertex2.pos.w) << std::endl;
		std::cout << clip_to_ndc_conversion_z(vertex3.pos.z, vertex3.pos.w) << std::endl;
		out=(t3v::vertex*)1;
	}

	return out;
}