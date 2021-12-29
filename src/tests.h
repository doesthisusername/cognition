#ifndef COG_TESTS_H
#define COG_TESTS_H
#include <stdbool.h>

#include "nk.h"

// needed because otherwise other TUs can't get the number of elements in `tests`.
#define TEST_COUNT 1

struct test {
    const char* name;
    bool (*draw_fn)(struct nk_context* ctx);
    void (*init_fn)(struct nk_context* ctx);
    void (*reset_fn)(struct nk_context* ctx);
};

extern const struct test tests[TEST_COUNT];

bool reaction_time(struct nk_context* ctx);
void reaction_time_init(struct nk_context* ctx);
void reaction_time_reset(struct nk_context* ctx);

#endif // COG_TESTS_H
