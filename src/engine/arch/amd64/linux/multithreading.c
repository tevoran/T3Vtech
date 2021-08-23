#include <te.h>
#ifdef __linux__

#include <sys/sysinfo.h>


//linux solution for the number of CPU threads
int te_num_procs() {
	return get_nprocs();
}

#endif