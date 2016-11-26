#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/scattering/fresnel.hpp>
#include <igloo/geometry/vector.hpp>
#include <limits>
#include <cmath>
#include <cassert>
#include <utility>


namespace igloo
{


class specular_reflection
{
  public:
    template<class Fresnel>
    inline specular_reflection(const color& reflectance,
                               Fresnel&& fresnel)
      : reflectance_(reflectance),
        fresnel_(std::forward<Fresnel>(fresnel))
    {}

    inline color operator()(const vector& wo, const vector& wi) const
    {
      // we return black because there is zero probability that wi and wo are reflections
      return black;
    }

    inline color operator()(const vector&) const
    {
      return black;
    }

    struct sample
    {
      public:
        inline sample(const vector& wi, const color& throughput)
          : wi_(wi), throughput_(throughput)
        {}

        inline const vector& wi() const
        {
          return wi_;
        }

        inline const color& throughput() const
        {
          return throughput_;
        }

        inline float probability_density() const
        {
          return 1.f;
        }

        inline bool is_delta_sample() const
        {
          return true;
        }

      private:
        vector wi_;
        color throughput_;
    };

    inline sample reflect(const vector& wo) const
    {
      // compute perfect specular reflection direction
      vector wi = vector(-wo[0], -wo[1], wo[2]);

      // note that we do not divide by cosine theta because we do not multiply
      // by .abs_cos_theta() for samples from delta distributions
      color throughput = fresnel_(wo[2]) * reflectance_;

      return {wi, throughput};
    }

    inline sample sample_direction(std::uint64_t u0, std::uint64_t u1, const vector& wo) const
    {
      // compute perfect specular reflection direction
      vector wi = vector(-wo[0], -wo[1], wo[2]);

      // note that we do not divide by cosine theta because we do not multiply
      // by .abs_cos_theta() for samples from delta distributions
      return sample(wi, fresnel_(wo[2]) * reflectance_); 
    }

  private:
    fresnel fresnel_;
    color reflectance_;   
};


} // end igloo

