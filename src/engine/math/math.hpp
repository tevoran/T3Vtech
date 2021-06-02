#pragma once
#include <te.hpp>

namespace t3v
{
	void barycentric_interpolation(
		const glm::ivec2 vertex1,
		const glm::ivec2 vertex2,
		const glm::ivec2 vertex3,
		const glm::ivec2 current_pixel,
		float& a,
		float& b,
		float& c
		);
} 