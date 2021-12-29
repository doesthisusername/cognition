#ifndef COG_TIMING_H
#define COG_TIMING_H
#include <stdint.h>
#include <time.h>

#define MS_PER_SEC 1000
#define US_PER_SEC 1000000
#define NS_PER_SEC 1000000000

// return a random `float` between 0 and 1, inclusive
float frand();

// return a random `float` between `min` and `max`, inclusive
float frand_range(float min, float max);

// returns current `CLOCK_MONOTONIC` value, through `time_coalesce()`
uintmax_t get_monotonic();

// coalesce seconds and nanoseconds for easier comparison
uintmax_t time_coalesce(struct timespec* time);

#endif // COG_TIMING_H
