#pragma once

#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/pi.hpp>
#include <igloo/scattering/color.hpp>

namespace igloo
{


class lambertian
{
  public:
    /*! Creates a new lambertian object from an albedo.
     *  \param albedo The color of this function's reflectance.
     */
    inline lambertian(const color& albedo)
      : m_albedo_over_pi(albedo / pi)
    {}

    inline lambertian()
      : lambertian(white)
    {}

    inline color operator()(const vector&, const vector&) const
    {
      return m_albedo_over_pi;
    } // end operator()

    inline color operator()(const vector&) const
    {
      return black;
    }

  private:
    color m_albedo_over_pi;
}; // end lambertian


} // end igloo

