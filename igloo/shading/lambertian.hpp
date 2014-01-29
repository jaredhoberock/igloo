#pragma once

#include <igloo/geometry/vector.hpp>
#include <igloo/shading/color.hpp>

namespace igloo
{


class lambertian
{
  public:
    /*! Creates a new lambertian object from an albedo.
     *  \param albedo The color of this function's reflectance.
     */
    inline lambertian(const color &albedo)
      : m_albedo_over_pi(albedo / 3.14159265359f)
    {}

    inline color operator()(const vector &wo, const vector &wi) const
    {
      return m_albedo_over_pi;
    } // end operator()

  private:
    color m_albedo_over_pi;
}; // end lambertian


} // end igloo

