#pragma once

#include <igloo/surfaces/surface.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/triangle_mesh.hpp>

namespace igloo
{


class sphere : public surface
{
  public:
    /*! Creates a new sphere.
     *  \param c The coordinates of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(const point &c, float r);

    /*! Creates a new sphere.
     *  \param cx The x-coordinate of the center of the sphere.
     *  \param cy The y-coordinate of the center of the sphere.
     *  \param cz The z-coordinate of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(float cx, float cy, float cz, float r); 

    /*! \return The center of the sphere.
     */
    inline const point &center() const
    {
      return m_center;
    } // end sphere::center()

    /*! \return The radius of the sphere.
     */
    inline float radius() const
    {
      return m_radius;
    } // end sphere::radius()

    /*! \return A triangle_mesh approximating this sphere.
     */
    virtual triangle_mesh triangulate() const;

  private:
    point m_center;
    float m_radius;
}; // end sphere


} // end igloo

