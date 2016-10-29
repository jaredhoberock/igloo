#pragma once

#include <igloo/geometry/triangle_mesh.hpp>
#include <igloo/geometry/differential_geometry.hpp>
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

    /*! \return The differential_geometry of the surface at coordinates (u0,u1).
     */
    virtual differential_geometry sample_surface(std::uint64_t u0, std::uint64_t u1) const = 0;

    /*! \return true if the given ray is intersected by this surface.
     */
    virtual bool is_intersected(const ray& r) const;

    /*! \return The value of the probability density function at the given surface point.
     */
    virtual float pdf(const differential_geometry& dg) const;
}; // end surface


} // end igloo

