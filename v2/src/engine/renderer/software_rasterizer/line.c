#include "line.h"

// This is temporary...
SDL_Color white;
white.r = 255;
white.g = 255;
white.b = 255;

inline void te_line(
	u16 *a,
	u16 *d,
	u16 *c // You will be used eventually
) {
	u16 ax = a[0];
	u16 ay = a[1];

	s16 dx = d[0];
	s16 dy = d[1];

	float m = sqrtf(dx*dx + dy*dy);

	for (u16 u = 0; u < m; ++u) SETPIXEL(
		ax + (s16)(dx*u/m),
		ay + (s16)(dy*u/m),
		white // Temporary
	);
}