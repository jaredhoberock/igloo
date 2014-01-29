#pragma once

#include <igloo/shading/lambertian.hpp>
#include <igloo/geometry/vector.hpp>
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


template<typename ScatteringDistributionFunction>
vector sample_with_basis(const ScatteringDistributionFunction &f,
                         const vector &tangent,
                         const vector &binormal,
                         const vector &normal,
                         float u0, float u1)
{
  // sample in f's local coordinate system
  vector result = f.sample(u0,u1);

  // transform to the given basis
  return result.x * tangent +
         result.y * binormal +
         result.z * normal;
} // sample_with_basis()


} // end igloo

