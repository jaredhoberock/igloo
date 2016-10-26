#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/geometry/vector.hpp>


namespace igloo
{


class specular_reflection
{
  public:
    inline specular_reflection(const color& reflectance,
                               const color& transmittance,
                               float eta_i,
                               float eta_t)
      : reflectance_(reflectance),
        transmittance_(transmittance),
        eta_i_(eta_i),
        eta_t_(eta_t)
    {}

    inline color operator()(const vector& wo, const vector& wi) const
    {
      // we return black because there is zero probability that wi and wo are reflections
      return color::black();
    }

    inline color operator()(const vector&) const
    {
      return color::black();
    }

  private:
    color reflectance_;   
    color transmittance_;
    float eta_i_; // XXX these are indices of refraction and could use better names
    float eta_t_;
};


} // end igloo

