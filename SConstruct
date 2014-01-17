env = Environment()

env.Append(CPPPATH = ['.', 'dependencies'])
env.Append(CPPFLAGS = ['-O3', '-std=c++11'])

sources = ['main.cpp',
           'ubuntu_13_10_workaround.cpp',
           'igloo/context.cpp',
           'igloo/geometry/transform.cpp',
           'igloo/surfaces/mesh.cpp',
           'igloo/surfaces/sphere.cpp',
           'igloo/viewers/test_viewer.cpp']

env.Program('demo', sources, LIBS = ['GL', 'GLU', 'glut', 'GLEW', 'pthread'])

