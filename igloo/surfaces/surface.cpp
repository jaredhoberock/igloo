#include <igloo/surfaces/surface.hpp>

namespace igloo
{


bool surface::is_intersected(const ray& r) const
{
  return static_cast<bool>(intersect(r));
} // end surface::is_intersected()


} // end igloo

