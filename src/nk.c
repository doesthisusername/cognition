#include <glad/gl.h>

#include <stdbool.h>

#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#include "nk.h"
#undef NK_IMPLEMENTATION
#undef NK_GLFW_GL4_IMPLEMENTATION

#define WIDTH 1200
#define HEIGHT 900
#define MAX_VERTEX_BUFFER (512 * 1024)
#define MAX_ELEMENT_BUFFER (512 * 1024)

struct xy window_size;
static GLFWwindow* window;

static void glfw_error(int err, const char* desc) {
    fprintf(stderr, "glfw error %d: %s\n", err, desc);
}

bool init_nk(struct nk_context** ctx) {
    // window and glfw init
    glfwSetErrorCallback(glfw_error);
    if(!glfwInit()) {
        fprintf(stderr, "glfw failed to init\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(WIDTH, HEIGHT, "cognition", NULL, NULL);
    glfwMakeContextCurrent(window);
    window_size.x = WIDTH;
    window_size.y = HEIGHT;

    // glad init
    gladLoaderLoadGL();
    glViewport(0, 0, WIDTH, HEIGHT);

    // nk init
    *ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    return true;
}

void shutdown_nk() {
    nk_glfw3_shutdown();
    glfwTerminate();
}

bool should_close() {
    return glfwWindowShouldClose(window);
}

void start_frame() {
    glfwPollEvents();
    nk_glfw3_new_frame();
}

void end_frame() {
    glfwGetWindowSize(window, &window_size.x, &window_size.y);
    glViewport(0, 0, window_size.x, window_size.y);
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
    glfwSwapBuffers(window);
}
