#ifndef ES_THREAD_H
#define ES_THREAD_H

/**
 * @file thread.h
 * @brief Thread-related utility functions for the ecomm library.
 *
 * This header provides helpers for setting and manipulating thread
 * metadata used for diagnostics and debugging (such as thread names).
 */

#include "defs.h"

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
 * @return 0 on success, or a non-zero errno/HRESULT-like error code on
 *         failure. ENOSYS may be returned when the platform does not
 *         support setting thread names.
 */
ECOMM_API int es_set_current_thread_name(const char* restrict_ name);

#ifdef __cplusplus
}
#endif

#endif /* ES_THREAD_H */
