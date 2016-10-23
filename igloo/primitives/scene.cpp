#include <igloo/primitives/scene.hpp>
#include <algorithm>

namespace igloo
{


optional<scene::intersection> scene::intersect(const ray& r) const
{
  optional<scene::intersection> result;

  std::for_each(surfaces_begin(), surfaces_end(), [&](const auto& surface)
  {
    auto i = surface.intersect(r);

    if(i && (!result || i->ray_parameter() < result->ray_parameter()))
    {
      result.emplace(*i, surface);
    }
  });

  return result;
} // end scene::intersect()


} // end igloo

