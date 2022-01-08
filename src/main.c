#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nk.h"
#include "tests.h"
#include "timing.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#define TESTS_PER_ROW 4

static const struct test* current_test = NULL;

int main(int argc, char** argv) {
    struct nk_context* ctx;
    if(!init_nk(&ctx)) {
        fprintf(stderr, "failed to init nuklear\n");
        return 1;
    }

    // default font
    {
        struct nk_font_atlas* atlas;
        nk_glfw3_font_stash_begin(&atlas);
        nk_glfw3_font_stash_end();
    }

    for(size_t i = 0; i < ARRAY_SIZE(tests); i++) {
        if(tests[i].init_fn) {
            tests[i].init_fn(ctx);
        }
    }

    uintmax_t last_now = 0;
    while(!should_close()) {
        // calculate the frame's delta time.
        // might be better to put in `nk.c`.
        const uintmax_t now = get_monotonic();
        ctx->delta_time_seconds = (now - last_now) / (double)NS_PER_SEC;
        last_now = now;

        start_frame();

        if(nk_begin(ctx, "cognition", nk_rect(0, 0, window_size.x, window_size.y), 0)) {
            if(!current_test) {
                nk_layout_row_dynamic(ctx, 0.0f, TESTS_PER_ROW);
                for(size_t i = 0; i < ARRAY_SIZE(tests); i++) {
                    if(nk_button_label(ctx, tests[i].name)) {
                        current_test = &tests[i];
                        tests[i].reset_fn(ctx);
                    }
                }
            }
            else {
                if(!current_test->draw_fn(ctx)) {
                    current_test = NULL;
                }
            }
        }
        nk_end(ctx);

        end_frame();
    }
    
    return 0;
}
