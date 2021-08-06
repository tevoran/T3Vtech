//works currently only on Linux

#include <te.h>

#ifdef __linux__
	#include <sys/sysinfo.h>
#endif

//linux solution for number of CPU threads
#ifdef __linux__

int te_num_procs() {
	return get_nprocs();
}

#endif
