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

float t3v::barycentric_interpolate_value(
	const float a,
	const float b,
	const float c,
	const float x,
	const float y,
	const float z
	)
{
	return a*x+b*y+c*z;
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

void t3v::barycentric_interpolation_line_optimized(
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
	)
{
	//first pixel
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

	//next pixel in the line
	current_pixel.x++;
	float tmp_a=(float)(
		(vertex2.x-current_pixel.x)
		*(vertex3.y-current_pixel.y)
		-(vertex3.x-current_pixel.x)
		*(vertex2.y-current_pixel.y))
		/div_const;
	float tmp_b=(float)(
		(vertex3.x-current_pixel.x)
		*(vertex1.y-current_pixel.y)
		-(vertex1.x-current_pixel.x)
		*(vertex3.y-current_pixel.y))
		/div_const;
	float tmp_c=1-tmp_a-tmp_b;

	delta_a=tmp_a-a;
	delta_b=tmp_b-b;
	delta_c=tmp_c-c;
}