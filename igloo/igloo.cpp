#include <igloo/igloo.hpp>
#include <igloo/viewers/test_viewer.hpp>
#include <iostream>
#include <cmath>

namespace igloo
{


igloo::igloo()
  : m_transform_stack(std::deque<transform>(1))
{}


void igloo::translate(float tx, float ty, float tz)
{
  mult_matrix_(transform::translate(tx,ty,tz));
} // end igloo::translate()


void igloo::rotate(float degrees, float rx, float ry, float rz)
{
  mult_matrix_(transform::rotate(degrees, rx, ry, rz));
} // end igloo::rotate()


void igloo::scale(float sx, float sy, float sz)
{
  mult_matrix_(transform::scale(sx, sy, sz)); 
} // end igloo::scale();


void igloo::mult_matrix(const float *m_)
{
  const float4x4 &m = *reinterpret_cast<const float4x4*>(m_);
  transform xfrm(m);

  mult_matrix_(xfrm);
} // end mult_matrix()


void igloo::mult_matrix_(const transform &xfrm)
{
  m_transform_stack.top() *= xfrm;
} // end mult_matrix_()


void igloo::sphere(float cx, float cy, float cz, float radius)
{
  typedef ::igloo::sphere sphere_type;
  m_spheres.push_back(sphere_type(cx,cy,cz,radius));
} // end igloo::sphere()


void igloo::render()
{
  float4x4 m(m_transform_stack.top().data());
  test_viewer v(m_spheres.back(), m);
  v.setWindowTitle("Hello, world!");
  v.show();
} // end igloo::render()


} // end igloo

