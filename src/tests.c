#include <stdbool.h>

#include "tests.h"

const struct test tests[TEST_COUNT] = {
    {
        .name = "reaction time",
        .draw_fn = reaction_time,
        .init_fn = NULL,
        .reset_fn = reaction_time_reset,
    },
    {
        .name = "latency",
        .draw_fn = latency,
        .init_fn = NULL,
        .reset_fn = latency_reset,
    },
};
