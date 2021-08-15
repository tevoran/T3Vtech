#ifndef TRIQ2_H
#define TRIQ2_H

inline void te_triq2_forward(
	u16 *a,
	u16 *b,
	u16 *c,
	float *t,
	u16 *p
);

inline void te_triq2_inverse(
	u16 *a,
	u16 *b,
	u16 *c,
	u16 *p,
	float *t
);

#endif