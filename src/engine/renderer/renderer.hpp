#pragma once

#include <te.hpp>

namespace t3v
{
	class renderer
	{
	private:
		int m_renderer_type=TE_RENDERER_NO_RENDERER;

	public:
		//projection matrix
		glm::mat4 m_projection_mat;
		float m_fov=90; // field of view in degrees
		float m_near_z_clip=0.1;
		float m_far_z_clip=1000;

		int m_resx=0;
		int m_resy=0;

		//settings set by the user
		bool m_is_fps_counter_active=false;

		renderer();
		~renderer();

		virtual void render();
		virtual void update();
	};
}