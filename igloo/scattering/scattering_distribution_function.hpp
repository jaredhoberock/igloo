#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/scattering/hemispherical_emission.hpp>
#include <igloo/scattering/lambertian.hpp>
#include <igloo/scattering/perfect_absorber.hpp>
#include <igloo/scattering/specular_reflection.hpp>
#include <igloo/geometry/vector.hpp>
#include <igloo/utility/variant.hpp>
#include <dependencies/distribution2d/distribution2d/unit_hemisphere_distribution.hpp>
#include <type_traits>

namespace igloo
{


class scattering_distribution_function
{
  private:
    using variant_type = std::experimental::variant<
      lambertian,
      hemispherical_emission,
      specular_reflection,
      perfect_absorber
    >;

  public:
    template<class BSDF,
             class = typename std::enable_if<
               std::is_constructible<variant_type,BSDF>::value
             >::type>
    inline scattering_distribution_function(const BSDF& other)
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

    class sample
    {
      public:
        inline sample(const color& throughput, const vector& wi, const float& probability_density)
          : throughput_(throughput), wi_(wi), probability_density_(probability_density)
        {}

        inline const color& throughput() const
        {
          return throughput_;
        }

        inline const vector& wi() const
        {
          return wi_;
        }

        inline float probability_density() const
        {
          return probability_density_;
        }

        inline bool is_delta_sample() const
        {
          return probability_density_ == 0;
        }

      private:
        color throughput_;
        vector wi_;
        float probability_density_;
    };

    inline sample sample_hemisphere(std::uint64_t u0, std::uint64_t u1, const vector& wo) const
    {
      dist2d::unit_hemisphere_distribution<vector> hemisphere;
      vector wi = hemisphere(u0, u1);
      return sample(operator()(wo,wi), wi, hemisphere.probability_density(wi));
    }

  private:
    variant_type m_impl;
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

