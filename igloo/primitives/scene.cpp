#include <igloo/primitives/scene.hpp>

namespace igloo
{


optional<scene::intersection> scene::intersect(const ray& r) const
{
  optional<scene::intersection> result;

  for(const auto& surface : *this)
  {
    auto i = surface.intersect(r);

    if(i && (!result || i->ray_parameter() < result->ray_parameter()))
    {
      result.emplace(*i, surface);
    }
  }

  return result;
} // end scene::intersect()


} // end igloo

