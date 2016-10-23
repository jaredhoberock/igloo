#include <igloo/primitives/scene.hpp>

namespace igloo
{


optional<intersection> scene::intersect(const ray& r) const
{
  optional<intersection> result;

  for(const auto& surface : *this)
  {
    auto intersection = surface.intersect(r);

    if(!result || intersection->ray_parameter() < result->ray_parameter())
    {
      result = intersection;
    }
  }

  return result;
} // end scene::intersect()


} // end igloo

