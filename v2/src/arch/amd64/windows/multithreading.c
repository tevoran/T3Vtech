#include <te.h>
#ifdef PTW32_VERSION

#include <pthread.h>

//Windows POSIX version for the number of CPU threads
int te_num_procs() {
	return pthread_num_processors_np();
}

#endif
