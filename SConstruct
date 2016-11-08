import sys

env = Environment()

env['CXX'] = 'clang'
env.Append(CPPPATH = ['.', 'dependencies'])
env.Append(CPPFLAGS = ['-O3', '-std=c++14'])

sources = ['cornell_box.cpp',
           'igloo/context.cpp',
           'igloo/geometry/transform.cpp',
           'igloo/materials/default_material.cpp',
           'igloo/materials/glass.cpp',
           'igloo/materials/light.cpp',
           'igloo/materials/material.cpp',
           'igloo/materials/matte.cpp',
           'igloo/primitives/scene.cpp',
           'igloo/surfaces/mesh.cpp',
           'igloo/surfaces/sphere.cpp',
           'igloo/surfaces/surface.cpp',
           'igloo/renderers/debug_renderer.cpp',
           'igloo/renderers/direct_lighting_renderer.cpp',
           'igloo/viewers/scene_viewer.cpp',
           'igloo/viewers/test_viewer.cpp']

if sys.platform == "darwin":
  env.AppendUnique(FRAMEWORKS=Split('OpenGL GLUT'))
  env.Program('cornell_box', sources, LIBS = ['GLEW', 'pthread', 'libc++'])
else:
  env.Program('cornell_box', sources, LIBS = ['GL', 'GLU', 'glut', 'GLEW', 'pthread', 'stdc++', 'm'])

