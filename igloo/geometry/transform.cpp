#include <igloo/geometry/transform.hpp>

namespace igloo
{


transform::transform()
  : transform(identity())
{}


transform::transform(const float4x4 &m)
  : m_xfrm(m), m_inv(m.inverse())
{}


transform::transform(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33)
  : m_xfrm(m00, m01, m02, m03,
           m10, m11, m12, m13,
           m20, m21, m22, m23,
           m30, m31, m32, m33),
    m_inv(m_xfrm.inverse())
{}


transform::transform(const float4x4 &xfrm, const float4x4 &inv)
  : m_xfrm(xfrm), m_inv(inv)
{}


transform transform::inverse() const
{
  return transform(m_inv, m_xfrm);
} // end transform::inverse()


const float *transform::data() const
{
  return m_xfrm;
} // end transform::data()


transform transform::operator*(const transform &rhs) const
{
  // XXX we could multiply the inverses here too to save a matrix inversion later
  float4x4 product = m_xfrm * rhs.m_xfrm;
  return transform(product);
} // end transform::operator*()


transform &transform::operator*=(const transform &rhs)
{
  transform result = (*this) * rhs;
  *this = result;
  return *this;
} // end transform::operator*=()


static point transform_point(const float4x4 &m, const point &p)
{
  float x = m(0,0)*p.x + m(0,1)*p.y + m(0,2)*p.z + m(0,3);
  float y = m(1,0)*p.x + m(1,1)*p.y + m(1,2)*p.z + m(1,3);
  float z = m(2,0)*p.x + m(2,1)*p.y + m(2,2)*p.z + m(2,3);
  float w = m(3,0)*p.x + m(3,1)*p.y + m(3,2)*p.z + m(3,3);

  if(w == 1.0f) return point(x,y,z);

  return point(x/w, y/w, z/w);
} // end transform_point()


static vector transform_vector(const float4x4 &m, const vector &v)
{
  float x = m(0,0)*v.x + m(0,1)*v.y + m(0,2)*v.z;
  float y = m(1,0)*v.x + m(1,1)*v.y + m(1,2)*v.z;
  float z = m(2,0)*v.x + m(2,1)*v.y + m(2,2)*v.z;

  return vector(x,y,z);
} // end transform_vector()


static normal transform_normal(const float4x4 &inv, const normal &n)
{
  float x = inv(0,0)*n.x + inv(1,0)*n.y + inv(2,0)*n.z;
  float y = inv(0,1)*n.x + inv(1,1)*n.y + inv(2,1)*n.z;
  float z = inv(0,2)*n.x + inv(1,2)*n.y + inv(2,2)*n.z;

  return normal(x,y,z);
} // end transform_normal()


point transform::operator()(const point &p) const
{
  return transform_point(m_xfrm, p);
} // end transform::operator()()


vector transform::operator()(const vector &v) const
{
  return transform_vector(m_xfrm, v);
} // end transform::operator()()


normal transform::operator()(const normal &n) const
{
  // note we send the inverse of the transform
  return transform_normal(m_inv, n);
} // end transform::operator()()


point transform::inverse_transform(const point &p) const
{
  return transform_point(m_inv, p);
} // end transform::inverse_transform()


normal transform::inverse_transform(const normal &n) const
{
  // note we send the transform itself, not its inverse
  return transform_normal(m_xfrm, n);
} // end transform::inverse_transform()


transform transform::identity()
{
  return transform(float4x4::identity(), float4x4::identity());
} // end transform::identity()


transform transform::translate(float dx, float dy, float dz)
{
  return transform(1, 0, 0, dx,
                   0, 1, 0, dy,
                   0, 0, 1, dz,
                   0, 0, 0,  1);
} // end transform::translate()


static float degrees_to_radians(float degrees)
{
  const float pi = 3.14159265f;
  return degrees * (pi / 180.0f);
} // end degrees_to_radians()


transform transform::rotate(float degrees, float rx, float ry, float rz)
{
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
   
  return transform(A);
} // end transform::rotate()


transform transform::scale(float sx, float sy, float sz)
{
  return transform(sx,  0,  0, 0,
                    0, sy,  0, 0,
                    0,  0, sz, 0,
                    0,  0,  0, 1);
} // end transform::scale()


} // end igloo

