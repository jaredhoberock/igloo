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


class specular_transmission
{
  public:
    inline specular_transmission(const color& transmittance,
                                 float eta_i, float eta_t)
      : transmittance_(transmittance),
        fresnel_(eta_i, eta_t)
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
          return 0;
        }

        inline bool is_delta_sample() const
        {
          return true;
        }

      private:
        vector wi_;
        color throughput_;
    };

    inline sample sample_direction(std::uint64_t u0, std::uint64_t u1, const vector& wo) const
    {
      vector wi = fresnel_.refract(wo);

      color throughput{0};

      if(wi != vector{0})
      {
        float cos_theta_o = wo[2];

        float one_over_eta = fresnel_.one_over_eta(cos_theta_o);

        // note that we do not divide by cosine theta because we do not multiply
        // by .abs_cos_theta() for samples from delta distributions
        throughput = one_over_eta * one_over_eta * (1.f - fresnel_(cos_theta_o)) * transmittance_;
      }

      return sample(wi, throughput);
    }

  private:
    color transmittance_;   
    fresnel_dielectric fresnel_;
}; // end specular_refraction


} // end igloo

