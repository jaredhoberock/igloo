#include <igloo/surfaces/sphere.hpp>

namespace igloo
{


sphere::sphere(const std::tuple<float,float,float> &c, float r)
  : m_center(c), m_radius(r)
{} // end sphere::sphere()


sphere::sphere(float cx, float cy, float cz, float r)
  : sphere(std::make_tuple(cx,cy,cz), r)
{} // end sphere::sphere()


} // end igloo

