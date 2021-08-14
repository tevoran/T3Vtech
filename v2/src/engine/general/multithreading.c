#include <te.h>
#include <threads.h>


//thread barrier implementation
te_thread_barrier te_thread_barrier_init(int num_threads) {
	te_thread_barrier barrier;
	barrier.num_threads=num_threads;
	barrier.waiting_threads=0;
	barrier.release_flag=TE_TRUE;
	mtx_init(&barrier.mutex, mtx_plain);
	return barrier;
};

bool te_thread_barrier_arrive(te_thread_barrier *barrier) {
	mtx_lock(&barrier->mutex);
	bool arrival_token=!barrier->release_flag;
	barrier->waiting_threads++;
	if(barrier->waiting_threads >= barrier->num_threads) {
		barrier->waiting_threads=0;
		barrier->release_flag=arrival_token;
	}
	mtx_unlock(&barrier->mutex);
	return arrival_token;
};

void te_thread_barrier_wait(te_thread_barrier *barrier, bool arrival_token) {
	mtx_lock(&barrier->mutex);
	while(barrier->release_flag!=arrival_token) {
		mtx_unlock(&barrier->mutex);
		mtx_lock(&barrier->mutex);
	}
	mtx_unlock(&barrier->mutex);
};

void te_thread_barrier_arrive_and_wait(te_thread_barrier *barrier) {
	te_thread_barrier_wait(barrier, te_thread_barrier_arrive(barrier));
};