#include <igloo/surfaces/surface.hpp>

namespace igloo
{


bool surface::is_intersected(const ray& r) const
{
  return static_cast<bool>(intersect(r));
} // end surface::is_intersected()


float surface::pdf(const differential_geometry&) const
{
  // we assume that all surface_primitives sample their surface area uniformly
  // XXX we could cache this value rather than recomputing it each time
  return 1.f / area();
} // end surface::pdf()


} // end igloo

