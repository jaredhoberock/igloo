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

    /*! \return The point on the surface at parametric coordinates uv.
     */
    virtual point point_on_surface(const parametric& uv) const = 0;

    /*! \return true if the given ray is intersected by this surface.
     */
    virtual bool is_intersected(const ray& r) const;
}; // end surface


} // end igloo

