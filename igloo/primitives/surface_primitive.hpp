#pragma once

#include <memory>
#include <igloo/surfaces/surface.hpp>
#include <igloo/shading/material.hpp>

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

    // XXX eliminate this
    inline const surface &surf() const
    {
      return *m_surface;
    }

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

