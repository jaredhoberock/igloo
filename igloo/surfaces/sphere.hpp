#pragma once

#include <tuple>

namespace igloo
{


class sphere
{
  public:
    /*! Creates a new sphere.
     *  \param c The coordinates of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(const std::tuple<float,float,float> &c, float r);

    /*! Creates a new sphere.
     *  \param cx The x-coordinate of the center of the sphere.
     *  \param cy The y-coordinate of the center of the sphere.
     *  \param cz The z-coordinate of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(float cx, float cy, float cz, float r); 

    /*! \return The center of the sphere.
     */
    inline const std::tuple<float,float,float> &center() const
    {
      return m_center;
    } // end sphere::center()

    /*! \return The radius of the sphere.
     */
    inline float radius() const
    {
      return m_radius;
    } // end sphere::radius()

  private:
    std::tuple<float,float,float> m_center;
    float m_radius;
}; // end sphere


} // end igloo

