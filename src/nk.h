#ifndef COG_NK_H
#define COG_NK_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT
#include <nk/nuklear.h>
#include <nk/nuklear_glfw_gl4.h>

#include <stdbool.h>

#define SET_NK_COLOR(x, cr, cg, cb, ca) x.r = cr; x.g = cg; x.b = cb; x.a = ca;

struct xy {
    int x, y;
};
extern struct xy window_size;

bool init_nk(struct nk_context** ctx);
void shutdown_nk();
bool should_close();
void start_frame();
void end_frame();

#endif // COG_NK_H
