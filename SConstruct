import sys

env = Environment()

env.Append(CPPPATH = ['.', 'dependencies'])
env.Append(CPPFLAGS = ['-O3', '-std=c++14'])

sources = ['main.cpp',
           'igloo/context.cpp',
           'igloo/geometry/transform.cpp',
           'igloo/shading/default_material.cpp',
           'igloo/shading/material.cpp',
           'igloo/shading/matte.cpp',
           'igloo/surfaces/mesh.cpp',
           'igloo/surfaces/sphere.cpp',
           'igloo/renderers/debug_renderer.cpp',
           'igloo/viewers/scene_viewer.cpp',
           'igloo/viewers/test_viewer.cpp']

if sys.platform == "darwin":
  env.AppendUnique(FRAMEWORKS=Split('OpenGL GLUT'))
  env.Program('demo', sources, LIBS = ['GLEW', 'pthread'])
else:
  env.Program('demo', sources, LIBS = ['GL', 'GLU', 'glut', 'GLEW', 'pthread'])

