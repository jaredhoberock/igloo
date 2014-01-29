#pragma once

#include <igloo/shading/lambertian.hpp>
#include <igloo/shading/color.hpp>

namespace igloo
{


// XXX this should eventually be implemented like boost::variant
class scattering_distribution_function
{
  public:
    inline scattering_distribution_function(const lambertian &other)
      : m_impl(other)
    {}

    inline color operator()(const vector &wo, const vector &wi) const
    {
      return m_impl(wo,wi);
    } // end operator()

  private:
    lambertian m_impl;
}; // end scattering_distribution_function


} // end igloo

