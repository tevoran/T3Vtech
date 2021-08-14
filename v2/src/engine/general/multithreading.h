#ifndef TE_MULTITHREADING_H
#define TE_MULTITHREADING_H

#include <threads.h>

//thread barrier
struct te_thread_barrier {
	int num_threads;
	int waiting_threads;
	bool release_flag;
	mtx_t mutex;
} typedef te_thread_barrier;

te_thread_barrier te_thread_barrier_init(int num_threads);
bool te_thread_barrier_arrive(te_thread_barrier *barrier);
void te_thread_barrier_wait(te_thread_barrier *barrier, bool arrival_token);
void te_thread_barrier_arrive_and_wait(te_thread_barrier *barrier);

int te_num_procs(); //is implemented in the arch directory



#endif