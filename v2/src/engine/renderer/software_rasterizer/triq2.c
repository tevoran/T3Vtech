#include "triq2.h"

inline void te_triq2_forward(
	u16 *a,
	u16 *b,
	u16 *c,
	float *t,
	u16 *p
) {
	u16 x = a[0];
	u16 y = a[1];

	float i = t[0];
	float j = t[1];

	p[0] = x + i*(b[0] - x) + j*(c[0] - x);
	p[1] = y + i*(b[1] - y) + j*(c[1] - y);
}

inline void te_triq2_inverse(
	u16 *a,
	u16 *b,
	u16 *c,
	u16 *p,
	float *t
) {
	u16 ax = a[0];
	u16 ay = a[1];

	u16 bx = b[0];
	u16 by = b[1];

	u16 cx = c[0];
	u16 cy = c[1];

	u16 px = p[0];
	u16 py = p[1];

	u16 i = cy - ay;
	u16 j = ay - by;
	u16 k = ay - py;

	float d =  ax*(by - cy) + bx*i + cx*j;
	t[0]    = (ax*(py - cy) + cx*k + px*i)/d;
	t[1]    = (ax*(by - py) + px*j - bx*k)/d;
}