#ifndef TWEEN_H
#define TWEEN_H

#define t_linear(a, b, x) (a + (x)*(b - (a)))

#define t_linear2(a, b, x) (
	a[0] = t_linear(a[0], b[0], x);
	a[1] = t_linear(a[1], b[1], x);
)

#define t_linear3(a, b, x) (
	a[0] = t_linear(a[0], b[0], x);
	a[1] = t_linear(a[1], b[1], x);
	a[2] = t_linear(a[2], b[2], x);
)

#define t_linear4(a, b, x) (
	a[0] = t_linear(a[0], b[0], x);
	a[1] = t_linear(a[1], b[1], x);
	a[2] = t_linear(a[2], b[2], x);
	a[3] = t_linear(a[3], b[3], x);
)

#endif