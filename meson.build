project('cognition', 'c',
    version : '0.0.2',
    license : 'MIT',
    default_options : [
        'c_std=c11',
        'warning_level=2',
        'werror=true',
    ],
)

cc = meson.get_compiler('c')
glfw = cc.find_library('glfw')
dl = cc.find_library('dl')
m = cc.find_library('m')

executable(meson.project_name(), 
    [
        'ext/glad/gl.c',
        'src/main.c',
        'src/nk.c',
        'src/tests.c',
        'src/timing.c',

        'src/tests/reaction_time.c',
        'src/tests/latency.c',
    ],
    dependencies : [glfw, dl, m],
    include_directories : 'ext',
)
