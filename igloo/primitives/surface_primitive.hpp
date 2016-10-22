#pragma once

#include <memory>
#include <igloo/surfaces/surface.hpp>
#include <igloo/shading/material.hpp>
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
      : m_surface(std::move(surf)),
        m_material(m)
    {}

    /*! \return A triangle_mesh approximating this surface_primitive.
     */
    inline triangle_mesh triangulate() const
    {
      return m_surface->triangulate();
    } // end triangulate();

    /*! Tests for intersection between a ray and this surface_primitive.
     *  \param r The ray of interest.
     *  \param nullopt if no intersection exists, otherwise the details of the intersection.
     */
    inline optional<intersection> intersect(const ray &r) const
    {
      return m_surface->intersect(r);
    } // end intersect()

    /*! \return This surface_primitive's material.
     */
    inline const material &get_material() const
    {
      return m_material;
    }

  private:
    std::unique_ptr<igloo::surface> m_surface;
    const material &m_material;
}; // end surface_primitive


} // end igloo

