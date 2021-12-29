#include <stdbool.h>
#include <stdio.h>

#include "nk.h"
#include "tests.h"
#include "timing.h"

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))
#define FONT_PATH "/usr/share/fonts/noto/NotoSans-Regular.ttf"

static const struct test* current_test = NULL;

int main(int argc, char** argv) {
    struct nk_context* ctx;
    if(!init_nk(&ctx)) {
        fprintf(stderr, "failed to init nuklear\n");
        return 1;
    }

    struct nk_font_atlas* atlas;
    nk_glfw3_font_stash_begin(&atlas);

    struct nk_font* font = nk_font_atlas_add_from_file(atlas, FONT_PATH, 26, NULL);

    nk_glfw3_font_stash_end();
    nk_style_set_font(ctx, &font->handle);

    for(size_t i = 0; i < ARRAY_SIZE(tests); i++) {
        if(tests[i].init_fn) {
            tests[i].init_fn(ctx);
        }
    }

    while(!should_close()) {
        start_frame();

        if(nk_begin(ctx, "cognition", nk_rect(0, 0, window_size.x, window_size.y), 0)) {
            if(!current_test) {
                nk_layout_row_dynamic(ctx, 0.0f, 4);
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
