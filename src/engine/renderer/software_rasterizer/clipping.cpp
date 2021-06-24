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
	}
}

//clipping is only done for the near z-plane
t3v::vertex* t3v::software_rasterizer::clipping(t3v::vertex& vertex1, t3v::vertex& vertex2, t3v::vertex& vertex3)
{
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



	return out;
}