//works currently only on Linux

#include <te.h>

#ifdef __linux__
	#include <sys/sysinfo.h>
#endif

#ifdef PTW32_VERSION
	#include <pthread.h>
#endif

//linux solution for the number of CPU threads
#ifdef __linux__
int te_num_procs() {
	return get_nprocs();
}
#endif

//Windows POSIX version for the number of CPU threads
#ifdef PTW32_VERSION
int te_num_procs() {
    return pthread_num_processors_np();
}
#endif