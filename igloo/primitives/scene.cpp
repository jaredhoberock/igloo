#include <igloo/primitives/scene.hpp>
#include <algorithm>

namespace igloo
{


optional<scene::intersection> scene::intersect(const ray& r) const
{
  optional<scene::intersection> result;

  for(const auto& surface : surfaces())
  {
    auto i = surface.intersect(r);

    if(i && (!result || i->ray_parameter() < result->ray_parameter()))
    {
      result.emplace(*i, surface);
    }
  }

  return result;
} // end scene::intersect()


bool scene::is_intersected(const ray& r) const
{
  return std::any_of(surfaces().begin(), surfaces().end(), [&](const auto& surface)
  {
    return surface.is_intersected(r);
  });

  //for(const auto& surface : surfaces())
  //{
  //  if(surface.is_intersected(r))
  //  {
  //    std::cout << "hit surface " << surface.get_material().name() << std::endl;
  //    return true;
  //  }
  //}

  return false;
} // end scene::intersect()


} // end igloo

