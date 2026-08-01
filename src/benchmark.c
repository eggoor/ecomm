#include "pch.h"

/*
 * Returns monotonic time in milliseconds.
 * Guaranteed not to go backward.
 */
uint64_t monotonic_ms(void)
{
#if defined(_WIN32)
    ULONGLONG t100ns = 0;

    /* Guaranteed-monotonic Windows timer */
    QueryUnbiasedInterruptTime(&t100ns);

    /* Convert 100ns units → ms */
    return (uint64_t)(t100ns / 10000ULL);

#elif defined(__APPLE__)

    static mach_timebase_info_data_t tb = { 0 };
    uint64_t t = mach_absolute_time();

    if (tb.denom == 0)
        mach_timebase_info(&tb);

    /* Convert to ns */
    uint64_t ns = t * tb.numer / tb.denom;

    return ns / 1000000ULL;

#else   /* Linux / POSIX */

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (uint64_t)ts.tv_sec * 1000ULL +
        (uint64_t)ts.tv_nsec / 1000000ULL;

#endif
}

void print_duration_ms(uint64_t duration_ms)
{
    uint64_t hours = duration_ms / (1000 * 60 * 60);
    duration_ms %= (1000 * 60 * 60);
    uint64_t minutes = duration_ms / (1000 * 60);
    duration_ms %= (1000 * 60);
    uint64_t seconds = duration_ms / 1000;
    duration_ms %= 1000;

    if (hours > 0)
        printf("%02" PRIu64 ":%02" PRIu64 ":%02" PRIu64 ".%03" PRIu64 "\n",
            hours, minutes, seconds, duration_ms);
    else if (minutes > 0)
        printf("%02" PRIu64 ":%02" PRIu64 ".%03" PRIu64 "\n",
            minutes, seconds, duration_ms);
    else
        printf("%2" PRIu64 ".%03" PRIu64 " s\n", seconds, duration_ms);
}
