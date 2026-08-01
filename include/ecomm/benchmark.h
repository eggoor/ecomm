#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "defs.h"

#ifdef __cplusplus
extern "C" {
#endif

ECOMM_API uint64_t monotonic_ms(void);
ECOMM_API void print_duration_ms(uint64_t ms);

#ifdef __cplusplus
}
#endif

#endif /* BENCHMARK_H */
