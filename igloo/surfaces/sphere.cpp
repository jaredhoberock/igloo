#include <igloo/surfaces/sphere.hpp>

namespace igloo
{


sphere::sphere(const point &c, float r)
  : m_center(c), m_radius(r)
{} // end sphere::sphere()


sphere::sphere(float cx, float cy, float cz, float r)
  : sphere(point(cx,cy,cz), r)
{} // end sphere::sphere()


} // end igloo

