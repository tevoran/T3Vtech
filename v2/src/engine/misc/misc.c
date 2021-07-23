#include <te.h>

void te_swap(void *ptr1, void *ptr2) {
	void *tmp_ptr;

	tmp_ptr=ptr1;
	ptr1=ptr2;
	ptr2=tmp_ptr;
}

