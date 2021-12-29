#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../nk.h"
#include "../tests.h"
#include "../timing.h"

#define DELAY_MIN 2.0f
#define DELAY_MAX 6.0f

static uintmax_t countdown_end;
static uintmax_t timing_start;
static bool timing;
static struct nk_style_button btn_style;
static char last_time[16];

bool reaction_time(struct nk_context* ctx) {
    nk_layout_row_dynamic(ctx, 200.0f, 1);
    const bool clicked = nk_button_label_styled(ctx, &btn_style, "click me when i turn green");

    if(!timing) {
        const uintmax_t now = get_monotonic();

        // go green
        if(now > countdown_end) {
            timing_start = now;
            timing = true;

            SET_NK_COLOR(btn_style.normal.data.color, 100, 221, 66, 96);
            SET_NK_COLOR(btn_style.hover.data.color, 100, 221, 66, 255);
        }
    }
    else {
        if(clicked) {
            const uintmax_t ms = (get_monotonic() - timing_start) / (NS_PER_SEC / MS_PER_SEC);
            snprintf(last_time, sizeof(last_time), "%zums", ms);

            reaction_time_reset(ctx);
        }
    }

    // see your last time
    nk_label(ctx, last_time, NK_TEXT_CENTERED);

    return true;
}

void reaction_time_reset(struct nk_context* ctx) {
    countdown_end = get_monotonic() + ((uintmax_t)frand_range(DELAY_MIN, DELAY_MAX) * NS_PER_SEC);
    
    timing = false;

    btn_style = ctx->style.button;
}
