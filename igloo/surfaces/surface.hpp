#pragma once

#include <igloo/geometry/triangle_mesh.hpp>

namespace igloo
{


class surface
{
  public:
    /*! Destructor does nothing.
     */
    inline virtual ~surface() {}

    /*! Tests for intersection between a ray and this surface.
     *  \param r The ray of interest.
     *  \param nullopt if no intersection exists, otherwise the differential geometry at the point of intersection.
     */
    virtual optional<std::tuple<float,parametric,normal>> intersect(const ray &r) const = 0;

    /*! \return A triangle_mesh approximating this surface.
     */
    virtual triangle_mesh triangulate() const = 0;
}; // end surface


} // end igloo

