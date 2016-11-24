#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/geometry/vector.hpp>
#include <limits>
#include <cmath>
#include <cassert>


namespace igloo
{


class specular_reflection
{
  public:
    // XXX why does this take transmittance? was this copied from glass?
    //     perhaps it's a fresnel parameter?
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

    inline sample sample_hemisphere(std::uint64_t u0, std::uint64_t u1, const vector& wo) const
    {
      // compute perfect specular reflection direction
      vector wi = vector(-wo[0], -wo[1], wo[2]);

      // XXX need to compute fresnel term here

      // we divide by cosine theta to turn the function into a brdf

      return sample(wi, reflectance_ / std::fabs(wi[2])); 
    }

  private:
    color reflectance_;   
    color transmittance_;
    float eta_i_; // XXX these are indices of refraction and could use better names
    float eta_t_;
};


} // end igloo

