#pragma once

#include <memory>
#include <igloo/surfaces/surface.hpp>
#include <igloo/materials/material.hpp>
#include <igloo/utility/optional.hpp>

namespace igloo
{


class surface_primitive
{
  public:
    /*! Creates a new surface_primitive
     *  \param surf A surface to take ownership of.
     *  \param m A material for this surface_primitive.
     */
    inline surface_primitive(std::unique_ptr<surface> &&surf, const material &m)
      : surface_(std::move(surf)),
        material_(m)
    {}

    /*! \return A triangle_mesh approximating this surface_primitive.
     */
    inline triangle_mesh triangulate() const
    {
      return surface_->triangulate();
    } // end triangulate();

    /*! Tests for intersection between a ray and this surface_primitive and returns the details of the intersection, if it exists.
     *  \param r The ray of interest.
     *  \param nullopt if no intersection exists, otherwise the details of the intersection.
     */
    inline optional<intersection> intersect(const ray &r) const
    {
      return surface_->intersect(r);
    } // end intersect()

    /*! Tests for intersection between a ray and this surface_primitive.
     *  \param r The ray of interest.
     *  \return false if no intersection exists; true, otherwise.
     */
    inline bool is_intersected(const ray& r) const
    {
      return surface_->is_intersected(r);
    } // end is_intersected()

    /*! \return This surface_primitive's material.
     */
    inline const igloo::material &material() const
    {
      return material_;
    }

    /*! \return The differential_geometry of the surface at coordinates (u0, u1).
     */
    inline differential_geometry sample_surface(std::uint64_t u0, std::uint64_t u1) const
    {
      return surface_->sample_surface(u0, u1);
    }

    /*! \return The value of the probability density function at the given surface location.
     */
    inline float pdf(const differential_geometry& dg) const
    {
      return surface_->pdf(dg);
    }

  private:
    std::unique_ptr<igloo::surface> surface_;
    const igloo::material &material_;
}; // end surface_primitive


} // end igloo

