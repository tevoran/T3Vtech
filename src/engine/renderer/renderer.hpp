#pragma once

#include <te.hpp>

namespace t3v
{
	class renderer
	{
	private:
		int m_renderer_type=TE_RENDERER_NO_RENDERER;

	public:
		int m_resx=0;
		int m_resy=0;

		renderer();
		~renderer();

		virtual void render();
		virtual void update();
	};
}