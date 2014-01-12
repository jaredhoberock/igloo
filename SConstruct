env = Environment()

env.Append(CPPPATH = ['.', 'dependencies'])
env.Append(CPPFLAGS = ['-std=c++11'])

sources = ['main.cpp',
           'ubuntu_13_10_workaround.cpp',
           'igloo/igloo.cpp',
           'igloo/surfaces/sphere.cpp',
           'igloo/viewers/test_viewer.cpp']

env.Program('demo', sources, LIBS = ['GL', 'GLU', 'glut', 'GLEW', 'pthread'])

