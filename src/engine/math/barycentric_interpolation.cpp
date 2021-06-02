#include <te.hpp>

void t3v::barycentric_interpolation(
	const glm::ivec2& vertex1,
	const glm::ivec2& vertex2,
	const glm::ivec2& vertex3,
	const glm::ivec2& current_pixel,
	float& a,
	float& b,
	float& c
	)
{
	float div=(vertex2.x-vertex1.x)*(vertex3.y-vertex2.y)-(vertex2.y-vertex1.y)*(vertex3.x-vertex2.x);
	a=(float)(
		(vertex2.x-current_pixel.x)
		*(vertex3.y-current_pixel.y)
		-(vertex3.x-current_pixel.x)
		*(vertex2.y-current_pixel.y))
		/div;
	b=(float)(
		(vertex3.x-current_pixel.x)
		*(vertex1.y-current_pixel.y)
		-(vertex1.x-current_pixel.x)
		*(vertex3.y-current_pixel.y))
		/div;
	c=1-a-b;
}

float t3v::barycentric_interpolation_optimized_div(
	const glm::ivec2& vertex1,
	const glm::ivec2& vertex2,
	const glm::ivec2& vertex3
	)
{
	return (float)((vertex2.x-vertex1.x)*(vertex3.y-vertex2.y)-(vertex2.y-vertex1.y)*(vertex3.x-vertex2.x));
}

void t3v::barycentric_interpolation_optimized(
	const glm::ivec2& vertex1,
	const glm::ivec2& vertex2,
	const glm::ivec2& vertex3,
	const glm::ivec2& current_pixel,
	const float div_const,
	float& a,
	float& b,
	float& c
	)
{
	a=(float)(
		(vertex2.x-current_pixel.x)
		*(vertex3.y-current_pixel.y)
		-(vertex3.x-current_pixel.x)
		*(vertex2.y-current_pixel.y))
		/div_const;
	b=(float)(
		(vertex3.x-current_pixel.x)
		*(vertex1.y-current_pixel.y)
		-(vertex1.x-current_pixel.x)
		*(vertex3.y-current_pixel.y))
		/div_const;
	c=1-a-b;
}