#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "timing.h"

float frand() {
    // basically interpolate from `0..RAND_MAX` `to 0..1`
    const float multiplier = (float)(1.0 / (double)RAND_MAX);

    return rand() * multiplier;
}

float frand_range(float min, float max) {
    // interpolate from `0..RAND_MAX` to `0..(max - min)`.
    // not piggybacking off `frand()` because of rounding (untested though).
    const float multiplier = (float)((max - min) / (double)RAND_MAX);

    return rand() * multiplier + min;
}

uintmax_t get_monotonic() {
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    return time_coalesce(&now);
}

uintmax_t time_coalesce(struct timespec* time) {
    return time->tv_sec * NS_PER_SEC + time->tv_nsec;
}
