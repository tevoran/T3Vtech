#pragma once
#include <te.hpp>

#define PI 3.141596

namespace t3v
{
	void barycentric_interpolation(
		const glm::ivec2& vertex1,
		const glm::ivec2& vertex2,
		const glm::ivec2& vertex3,
		const glm::ivec2& current_pixel,
		float& a,
		float& b,
		float& c
		);

	float barycentric_interpolate_value(
		const float a,
		const float b,
		const float c,
		const float x,
		const float y,
		const float z
		);

	//these functions are for an optimized engine intern use
	float barycentric_interpolation_optimized_div(
		const glm::ivec2& vertex1,
		const glm::ivec2& vertex2,
		const glm::ivec2& vertex3
		);

	void barycentric_interpolation_optimized(
		const glm::ivec2& vertex1,
		const glm::ivec2& vertex2,
		const glm::ivec2& vertex3,
		const glm::ivec2& current_pixel,
		const float div_const,
		float& a,
		float& b,
		float& c
		);

	void barycentric_interpolation_line_optimized(
		const glm::ivec2& vertex1,
		const glm::ivec2& vertex2,
		const glm::ivec2& vertex3,
		glm::ivec2 current_pixel,
		const float div_const,
		float& a,
		float& b,
		float& c,
		float& delta_a,
		float& delta_b,
		float& delta_c
		);


	//rotation stuff
	glm::mat4 rotation_quaternion(glm::mat4& rotation_mat_in, glm::vec3& rotation_axis, float rotation_degrees);


} 	