#pragma once

#include <igloo/geometry/triangle_mesh.hpp>
#include <igloo/surfaces/intersection.hpp>
#include <igloo/utility/optional.hpp>

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
     *  \param nullopt if no intersection exists, otherwise the details of the intersection.
     */
    virtual optional<intersection> intersect(const ray &r) const = 0;

    /*! \return A triangle_mesh approximating this surface.
     */
    virtual triangle_mesh triangulate() const = 0;

    /*! \return The surface area of this surface.
     */
    virtual float area() const = 0;
}; // end surface


} // end igloo

