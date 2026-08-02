#ifndef THREADS_H
#define THREADS_H

#include "defs.h"

/**
 * @file threads.h
 * @brief Thread-related utility functions for the ecomm library.
 *
 * This header provides helpers for setting and manipulating thread
 * metadata used for diagnostics and debugging (such as thread names).
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the current thread's name.
 *
 * Attempts to assign a human-readable name to the currently executing
 * thread. Behavior and availability may vary by platform; the function
 * will return an appropriate error code if the operation is not
 * supported on the current platform.
 *
 * @param name NUL-terminated UTF-8 name to set for the current thread.
 *             Must not be NULL or empty.
 * @return 0 on success, or a non-zero errno/HrcULT-like error code on
 *         failure. ENOSYS may be returned when the platform does not
 *         support setting thread names.
 */
ECOMM_API int es_set_curr_thread_name(const char* restrict_ name);

#if defined(__APPLE__) || defined(__MACH__)

#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct thrd {
	pthread_t thread;
	struct thrd_data* data;
} thrd_t;

typedef pthread_mutex_t mtx_t;
typedef pthread_cond_t cnd_t;
typedef pthread_key_t tss_t;
typedef pthread_once_t once_flag;
typedef int (*thrd_start_t)(void *);
typedef void (*tss_dtor_t)(void *);

enum {
	thrd_success = 0,
	thrd_busy,
	thrd_error,
	thrd_nomem,
	thrd_timedout
};

enum {
	mtx_plain = 0,
	mtx_recursive = 1,
	mtx_timed = 2
};

#define ONCE_FLAG_INIT PTHREAD_ONCE_INIT

#define thrd_yield() sched_yield()

#define mtx_lock(m) pthread_mutex_lock(m)
#define mtx_unlock(m) pthread_mutex_unlock(m)
#define mtx_destroy(m) pthread_mutex_destroy(m)

#define cnd_signal(c) pthread_cond_signal(c)
#define cnd_broadcast(c) pthread_cond_broadcast(c)
#define cnd_wait(c, m) pthread_cond_wait((c), (m))
#define cnd_destroy(c) pthread_cond_destroy(c)

#define tss_delete(k) pthread_key_delete(k)
#define tss_get(k) pthread_getspecific(k)
#define tss_set(k, v) pthread_setspecific((k), (v))

#define call_once(f, fn) pthread_once((f), (fn))

struct thrd_data {
	int (*func)(void *);
	void *arg;
	int rcult;
};

static void* thrd_start(void* arg)
{
	struct thrd_data* data = arg;
	data->rcult = data->func(data->arg);

	return NULL;
}

static inline int thrd_create(thrd_t* thr, thrd_start_t func, void* arg)
{
	thr->data = malloc(sizeof(*thr->data));
	if (!thr->data)
		return thrd_nomem;

	thr->data->func = func;
	thr->data->arg = arg;

	if (pthread_create(&thr->thread, NULL, thrd_start, thr->data) != 0)	{
		free(thr->data);
		thr->data = NULL;
		return thrd_error;
	}

	return thrd_success;
}

static inline int thrd_join(thrd_t thr, int* prc)
{
	if (pthread_join(thr.thread, NULL) != 0)
		return thrd_error;

	if (prc)
		*prc = thr.data->rcult;

	free(thr.data);

	return thrd_success;
}

static inline void thrd_exit(int rc)
{
	pthread_exit((void*)(intptr_t)rc);
}

static inline int thrd_detach(thrd_t thr)
{
	if (pthread_detach(thr.thread) != 0)
		return thrd_error;

	free(thr.data);

	return thrd_success;
}

static inline int thrd_sleep(const struct timespec* duration,
	struct timespec* remaining)
{
	return nanosleep(duration, remaining);
}

static inline thrd_t thrd_current(void)
{
	thrd_t thr = {
		.thread = pthread_self(),
		.data = NULL};

	return thr;
}

static inline int thrd_equal(thrd_t lhs, thrd_t rhs)
{
	return pthread_equal(lhs.thread, rhs.thread);
}

static inline int mtx_init(mtx_t *mtx, int type)
{
	pthread_mutexattr_t attr;

	if (pthread_mutexattr_init(&attr) != 0)
		return thrd_error;

	if (type & mtx_recursive)
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	int rc = pthread_mutex_init(mtx, &attr);

	pthread_mutexattr_destroy(&attr);

	return rc == 0 ? thrd_success : thrd_error;
}

static inline int cnd_init(cnd_t* cond)
{
	return pthread_cond_init(cond, NULL) == 0 ? thrd_success : thrd_error;
}

static inline int cnd_timedwait(cnd_t* cond, mtx_t* mtx,
	const struct timespec *ts)
{
	int rc = pthread_cond_timedwait(cond, mtx, ts);

	if (rc == 0)
		return thrd_success;

	if (rc == ETIMEDOUT)
		return thrd_timedout;

	return thrd_error;
}

static inline int tss_create(tss_t* key, tss_dtor_t dtor)
{
	return pthread_key_create(key, dtor) == 0 ? thrd_success : thrd_error;
}

#endif /* __APPLE__ */

#ifdef __cplusplus
}
#endif

#endif // THREADS_H
