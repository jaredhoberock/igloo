#include <igloo/igloo.hpp>
#include <igloo/viewers/test_viewer.hpp>
#include <iostream>

namespace igloo
{


void igloo::sphere(float cx, float cy, float cz, float radius)
{
  typedef ::igloo::sphere sphere_type;
  m_spheres.push_back(sphere_type(cx,cy,cz,radius));
} // end igloo::sphere()


void igloo::render()
{
  test_viewer v(m_spheres.back());
  v.setWindowTitle("Hello, world!");
  v.show();
} // end igloo::render()


} // end igloo

