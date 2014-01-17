#pragma once

#include <memory>
#include <igloo/surfaces/surface.hpp>

namespace igloo
{


class surface_primitive
{
  public:
    /*! Creates a new surface_primitive
     *  \param surf A surface to take ownership of.
     */
    inline surface_primitive(std::unique_ptr<surface> &&surf)
      : m_surface(std::move(surf))
    {}

    /*! \return A triangle_mesh approximating this surface_primitive.
     */
    inline triangle_mesh triangulate() const
    {
      return m_surface->triangulate();
    } // end triangulate();

  private:
    std::unique_ptr<surface> m_surface;
}; // end surface_primitive


} // end igloo

