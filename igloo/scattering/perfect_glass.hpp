#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/scattering/specular_reflection.hpp>
#include <igloo/scattering/specular_transmission.hpp>
#include <igloo/geometry/vector.hpp>
#include <distribution2d/distribution2d/unit_interval_distribution.hpp>
#include <limits>
#include <cmath>
#include <cassert>
#include <utility>


namespace igloo
{


class perfect_glass
{
  public:
    inline perfect_glass(const color& reflectance,
                         const color& transmittance,
                         float eta_i, float eta_t)
      : reflection_(reflectance, fresnel_dielectric(eta_i, eta_t)),
        transmission_(transmittance, eta_i, eta_t)
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
        inline sample(const vector& wi, const color& throughput, float probability_density)
          : wi_(wi), throughput_(throughput), probability_density_(probability_density)
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
          return probability_density_;
        }

        inline bool is_delta_sample() const
        {
          return true;
        }

      private:
        vector wi_;
        color throughput_;
        float probability_density_;
    };

    inline sample sample_direction(std::uint64_t u0, std::uint64_t u1, const vector& wo) const
    {
      // try both bsdfs
      auto reflected = reflection_.reflect(wo);
      auto transmitted = transmission_.transmit(wo);

      // compute the importance of either sample
      float reflected_importance = luminance(reflected.throughput());
      float transmitted_importance = luminance(transmitted.throughput());

      // the probability of selecting the reflected direction is proportional to its importance
      float reflected_probability = reflected_importance / (reflected_importance + transmitted_importance);

      dist2d::unit_interval_distribution<> unit_interval;
      if(unit_interval(u0) < reflected_probability)
      {
        return sample(reflected.wi(), reflected.throughput(), reflected_probability);
      }

      return sample(transmitted.wi(), transmitted.throughput(), 1.f - reflected_probability);
    }

  private:
    specular_reflection reflection_;
    specular_transmission transmission_;
};


} // end igloo

