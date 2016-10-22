#pragma once

#include <igloo/shading/lambertian.hpp>
#include <igloo/shading/hemispherical_emission.hpp>
#include <igloo/geometry/vector.hpp>
#include <igloo/shading/color.hpp>
#include <igloo/utility/variant.hpp>

namespace igloo
{


class scattering_distribution_function
{
  public:
    inline scattering_distribution_function(const lambertian& other)
      : m_impl(other)
    {}

    inline scattering_distribution_function(const hemispherical_emission& other)
      : m_impl(other)
    {}

  private:
    struct bidirectional_visitor
    {
      const vector& wo;
      const vector& wi;

      template<class F>
      color operator()(const F& f) const
      {
        return f(wo,wi);
      }
    };

    struct unidirectional_visitor
    {
      const vector& wo;

      template<class F>
      color operator()(const F& f) const
      {
        return f(wo);
      }
    };

  public:
    inline color operator()(const vector &wo, const vector &wi) const
    {
      bidirectional_visitor visitor{wo,wi};
      return std::experimental::visit(visitor, m_impl);
    } // end operator()

    inline color operator()(const vector& wo) const
    {
      unidirectional_visitor visitor{wo};
      return std::experimental::visit(visitor, m_impl);
    }

  private:
    std::experimental::variant<lambertian, hemispherical_emission> m_impl;
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

