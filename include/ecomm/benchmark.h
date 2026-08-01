#ifndef ES_BENCHMARK_H
#define ES_BENCHMARK_H

#include <stdint.h>

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get current monotonic time in milliseconds.
 *
 * Monotonic time is guaranteed not to go backwards and is suitable for
 * measuring elapsed time. The epoch is unspecified (implementation defined).
 *
 * @return Current monotonic time in milliseconds.
 */
ECOMM_API uint64_t es_get_monotonic_time_ms(void);

/**
 * @brief Print an elapsed duration given in milliseconds in a human-readable form.
 *
 * The function converts the provided duration (milliseconds) into a formatted
 * string such as "HH:MM:SS.mmm", "MM:SS.mmm", or "S.mmm s" and writes it to
 * stdout.
 *
 * @param duration_ms Duration in milliseconds to print.
 */
ECOMM_API void es_pretty_print_elapsed_time(uint64_t duration_ms);

#ifdef __cplusplus
}
#endif

#endif /* ES_BENCHMARK_H */
