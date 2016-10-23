#pragma once

#include <vector>
#include <igloo/primitives/surface_primitive.hpp>

namespace igloo
{


class scene : public std::vector<surface_primitive>
{
  public:
    /*! Tests for intersection between a ray and this scene.
     *  \param r The ray of interest.
     *  \param nullopt if no interest exists, otherwise the details of the intersection.
     */
    optional<intersection> intersect(const ray &r) const;
};


} // end igloo

