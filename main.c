#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <SDL2/SDL.h>

#define SETPIXEL(x, y, c) pixels[x + w*y] = c

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

u8 main() {
	u16 p0[2];
	u16 p1[2];
	u16 p2[2];

	u16 c0[] = {255, 0, 0};
	u16 c1[] = {0, 255, 0};
	u16 c2[] = {0, 0, 255};

	u16 vs[] = {1280, 720};
	const u16 w = *vs;

	float f[2];
	u16 p[2];
	SDL_Color c;

	SDL_Event event;

	void qp2f(u16 *a, u16 *b, u16 *c, float *x, u16 *p) {
		u16 ax = a[0];
		u16 ay = a[1];

		u16 bx = b[0];
		u16 by = b[1];

		u16 cx = c[0];
		u16 cy = c[1];

		float xx = f[0];
		float xy = f[1];

		p[0] = ax + xx*(bx - ax) + xy*(cx - ax);
		p[1] = ay + xx*(by - ay) + xy*(cy - ay);
	}

	void qp2i(u16 *a, u16 *b, u16 *c, u16 *p, float *x) {
		u16 ax = a[0];
		u16 ay = a[1];

		u16 bx = b[0];
		u16 by = b[1];

		u16 cx = c[0];
		u16 cy = c[1];

		u16 px = p[0];
		u16 py = p[1];

		u32 d = ax*(by - cy) + bx*(cy - ay) + cx*(ay - by);

		f[0] =  (float)((cy - ay)*px + cx*(ay - py) + ax*(py - cy))/d;
		f[1] = -(float)((by - ay)*px + bx*(ay - py) + ax*(py - by))/d;
	}

	SDL_Init(
		SDL_INIT_TIMER |
		SDL_INIT_VIDEO |
		SDL_INIT_EVENTS
	);

	SDL_Window *window = SDL_CreateWindow(
		"Der fenster",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		vs[0],
		vs[1],
		0
	);

	p0[0] = rand()%vs[0];
	p0[1] = rand()%vs[1];

	p1[0] = rand()%vs[0];
	p1[1] = rand()%vs[1];

	p2[0] = rand()%vs[0];
	p2[1] = rand()%vs[1];

	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Color *pixels = surface->pixels;

	inline void tri(u16 *p0, u16 *p1, u16 *p2, u16 *c0, u16 *c1, u16 *c2) {
		for (u16 px = fmin(p0[0], fmin(p1[0], p2[0])); px < fmax(p0[0], fmax(p1[0], p2[0])); ++px)
		for (u16 py = fmin(p0[1], fmin(p1[1], p2[1])); py < fmax(p0[1], fmax(p1[1], p2[1])); ++py) {
			p[0] = px;
			p[1] = py;

			qp2i(p0, p1, p2, p, f);

			float fx = f[0];
			float fy = f[1];

			if (
				fx >= 0 &&
				fy >= 0 &&
				fx + fy < 1
			) {
				c.r = 255;
				c.g = 255;
				c.b = 255;

				SETPIXEL(px, py, c);
			}
		}
	}

	u32 t0 = SDL_GetTicks();

	for (u32 f = 0;; ++f) {
		// Event
		SDL_PollEvent(&event);

		switch (event.type) case SDL_QUIT: {
			u32 t1 = SDL_GetTicks();

			printf("%f*f/s average\n", 1000.0f*f/(t1 - t0));

			SDL_DestroyWindow(window);
			SDL_Quit();

			return 0;
		}

		// Render
		{
			tri(p0, p1, p2, c0, c1, c2);

			SDL_UpdateWindowSurface(window);
		}
	}
}