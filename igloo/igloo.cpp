#include <igloo/igloo.hpp>
#include <igloo/viewers/test_viewer.hpp>
#include <iostream>
#include <cmath>

namespace igloo
{


igloo::igloo()
  : m_matrix_stack(std::deque<float4x4>(1,float4x4::identity()))
{}


void igloo::translate(float tx, float ty, float tz)
{
  // XXX this code for a translation matrix should go in a transform class
  float4x4 m(1, 0, 0, tx,
             0, 1, 0, ty,
             0, 0, 1, tz,
             0, 0, 0,  1);
  mult_matrix(m);
} // end igloo::translate()


static float degrees_to_radians(float degrees)
{
  const float pi = 3.14159265f;
  return degrees * pi / 180.0f;
}


void igloo::rotate(float degrees, float rx, float ry, float rz)
{
  // XXX this code for a rotation matrix should go in a transform class
  float4x4 A;
  float length = std::sqrt((rx*rx) + (ry*ry) + (rz*rz));
  float a = rx / length;
  float b = ry / length;
  float c = rz / length;
  float aa = a * a;
  float bb = b * b;
  float cc = c * c;
  float sine = std::sin(degrees_to_radians(-degrees));
  float cosine = std::cos(degrees_to_radians(-degrees));
  float omcos = 1.0f - cosine;

  A(0,0) = aa + (1.0f - aa) * cosine;
  A(1,1) = bb + (1.0f - bb) * cosine;
  A(2,2) = cc + (1.0f - cc) * cosine;
  A(0,1) = a * b * omcos + c * sine;
  A(0,2) = a * c * omcos - b * sine;
  A(1,0) = a * b * omcos - c * sine;
  A(1,2) = b * c * omcos + a * sine;
  A(2,0) = a * c * omcos + b * sine;
  A(2,1) = b * c * omcos - a * sine;
  A(0,3) = A(1,3) = A(2,3) = A(3,0) = A(3,1) = A(3,2) = 0.0f;
  A(3,3) = 1.0f;
   
  mult_matrix(A);
} // end igloo::rotate()


void igloo::scale(float sx, float sy, float sz)
{
  // XXX this code for a rotation matrix should go in a transform class
  float4x4 m(sx,  0,  0, 0,
              0, sy,  0, 0,
              0,  0, sz, 0,
              0,  0,  0, 1);

  mult_matrix(m); 
} // end igloo::scale();


void igloo::mult_matrix(const float *m_)
{
  const float4x4 &m = *reinterpret_cast<const float4x4*>(m_);

  m_matrix_stack.top() *= m;
} // end mult_matrix()


void igloo::sphere(float cx, float cy, float cz, float radius)
{
  typedef ::igloo::sphere sphere_type;
  m_spheres.push_back(sphere_type(cx,cy,cz,radius));
} // end igloo::sphere()


void igloo::render()
{
  test_viewer v(m_spheres.back(), m_matrix_stack.top());
  v.setWindowTitle("Hello, world!");
  v.show();
} // end igloo::render()


} // end igloo

