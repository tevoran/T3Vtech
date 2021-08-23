#include <te.h>


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
	) {

	float div=
		(v2_x-v1_x)*(v3_y-v2_y)
		-(v2_y-v1_y)*(v3_x-v2_x);
	*a_out=
		((v2_x-current_x)*(v3_y-current_y)
		-(v3_x-current_x)*(v2_y-current_y))
		/div;
	*b_out=
		((v3_x-current_x)*(v1_y-current_y)
		-(v1_x-current_x)*(v3_y-current_y))
		/div;
	*c_out=1-(*b_out)-(*a_out);
}