#include "misc.h"

void *void_ptr;

void te_swap(void *a, void *b) {
	void_ptr = *(void**)b;
	*(void**)b = *(void**)a;
	*(void**)a = void_ptr;
}