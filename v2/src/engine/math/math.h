#ifndef TE_MATH_H
#define TE_MATH_H


void te_barycentric_interpolation(
	float v1_x,
	float v1_y,
	float v2_x,
	float v2_y,
	float v3_x,
	float v3_y,
	float current_x,
	float current_y,
	float *a_out,
	float *b_out,
	float *c_out
	);

#endif