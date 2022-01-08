#include <stdbool.h>
#include <stdio.h>

#include "../nk.h"
#include "../tests.h"
#include "../timing.h"

#define STR_(x) #x
#define STR(x) STR_(x)

#define MAX_ROUND 200.0f
#define ROUND_TIME_SEC 1.0f
#define SAMPLE_N 10

static bool rounding;
static struct nk_style_button btn_style;
static size_t sample_i;
static float samples[SAMPLE_N];
static char label_text[64];
static char result_text[64];

bool latency(struct nk_context* ctx) {
    if((rounding && btn_style.rounding >= MAX_ROUND) || (!rounding && btn_style.rounding <= 0.0f)) {
        rounding = !rounding;
    }
    btn_style.rounding += (rounding ? 1.0f : -1.0f) * (ctx->delta_time_seconds * (ROUND_TIME_SEC * MAX_ROUND));
    if(btn_style.rounding < 0.0f) {
        btn_style.rounding = 0.0f;
    }

    if(btn_style.rounding > 0.0f) {
        btn_style.hover.data.color.g = (MAX_ROUND - btn_style.rounding) * (UINT8_MAX / MAX_ROUND);
    }
    else {
        btn_style.hover.data.color.g = 0;
    }
    btn_style.active.data = btn_style.hover.data;

    nk_layout_row_static(ctx, 500, 500, 2);

    const bool clicked = nk_button_label_styled(ctx, &btn_style, "click me");

    snprintf(label_text, sizeof(label_text), "click when fully square and green (%zu / " STR(SAMPLE_N) ")", sample_i);
    nk_label(ctx, label_text, NK_TEXT_CENTERED);

    if(clicked) {
        samples[sample_i++] = (rounding ? 1.0f : -1.0f) * (btn_style.rounding / MAX_ROUND) * ROUND_TIME_SEC;

        if(sample_i == SAMPLE_N) {
            float avg = 0.0f;
            float min = 100.0f;
            float max = -100.0f;
            for(size_t i = 0; i < SAMPLE_N; i++) {
                const float sample = samples[i];
                avg += sample;

                if(sample < min) {
                    min = sample;
                }
                else if(sample > max) {
                    max = sample;
                }
            }
            avg /= SAMPLE_N;

            snprintf(result_text, sizeof(result_text), "avg %0.3fs; min %0.3fs; max %0.3fs", avg, min, max);
            latency_reset(ctx);
        }
    }

    if(result_text[0] != '\0') {
        nk_layout_row_dynamic(ctx, 200.0f, 1);
        nk_label(ctx, result_text, NK_TEXT_CENTERED);
    }

    return true;
}

void latency_reset(struct nk_context* ctx) {
    btn_style = ctx->style.button;
    btn_style.rounding = 0;

    sample_i = 0;
    rounding = true;
}
