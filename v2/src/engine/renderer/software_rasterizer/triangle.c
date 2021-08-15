#include "triangle.h"

inline void te_triangle(
	u16 *p0,
	u16 *p1,
	u16 *p2,
	u16 *c0,
	u16 *c1,
	u16 *c2
) {
	//switch (a[1] > b[1]) case 1: te_swap(&a, &b);
	//switch (b[1] > c[1]) case 1: te_swap(&b, &c);
	//switch (c[1] > a[1]) case 1: te_swap(&c, &a);

	for (u16 px = fmin(fmin(p0[0], p1[0]), p2[0]); px < fmax(fmax(p0[0], p1[0]), p2[0]); ++px)
	for (u16 py = fmin(fmin(p0[1], p1[1]), p2[1]); py < fmax(fmax(p0[1], p1[1]), p2[1]); ++py) {
		p[0] = px;
		p[1] = py;

		te_triq2_inverse(p0, p1, p2, p, f);

		float fx = f[0];
		float fy = f[1];

		if (
			fx >= 0 &&
			fy >= 0 &&
			fx + fy < 1
		) {
			color.r = 255;
			color.g = 255;
			color.b = 255;

			SETPIXEL(px, py, color);
		}
	}
}