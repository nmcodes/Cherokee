#ifndef _THPOOL_
#define _THPOOL_

typedef struct thpool_* threadpool;

threadpool thpool_init(int num_threads);
int thpool_add_work(threadpool, void (*function_p)(void*), void* arg_p);
void thpool_wait(threadpool);
void thpool_pause(threadpool);
void thpool_resume(threadpool);
void thpool_destroy(threadpool);
int thpool_num_threads_working(threadpool);

#endif
