#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/utility/variant.hpp>
#include <cmath>


namespace igloo
{


class fresnel_no_op
{
  public:
    inline color operator()(float) const
    {
      return color::white();
    }
};


inline color approximate_fresnel_absorption_coefficient(const color& reflectance)
{
  color result = reflectance;

  result /= (1.f - result);

  // saturate before the square root
  result = saturate(result);

  result = sqrt(result);

  result *= 2.f;

  return result;
}


struct approximate_absorption_t {};
constexpr approximate_absorption_t approximate_absorption{};


class fresnel_conductor
{
  public:
    inline fresnel_conductor(const color& eta, const color& k)
      : eta_(eta), k_(k)
    {}

    inline fresnel_conductor(approximate_absorption_t, const color& reflectance, const color& eta)
      : fresnel_conductor(eta, approximate_fresnel_absorption_coefficient(reflectance))
    {}

    inline static color evaluate(float cos_theta_i, const color& eta, const color& k)
    {
      float c2 = cos_theta_i*cos_theta_i;
      color cos_theta_i_2(c2, c2, c2);
      color tmp = cos_theta_i_2 * (eta*eta + k*k);
      
      color r_parallel2 = (tmp - (2.f * eta * cos_theta_i) + color::white()) /
                          (tmp + (2.f * eta * cos_theta_i) + color::white());
      color tmp_f = eta*eta + k*k;
      
      color r_perp2 = (tmp_f - (2.f * eta * cos_theta_i) + cos_theta_i_2) /
                      (tmp_f + (2.f * eta * cos_theta_i) + cos_theta_i_2);
      
      return (r_parallel2 + r_perp2) / 2.f;
    }

    inline color operator()(float cos_theta_i) const
    {
      return evaluate(std::fabs(cos_theta_i), eta_, k_);
    }

  private:
    color eta_;
    color k_;
};


class fresnel_dielectric
{
  public:
    inline fresnel_dielectric(float eta_i, float eta_t)
      : eta_i_(eta_i), eta_t_(eta_t)
    {}

    template<class FloatOrColor>
    inline static color evaluate(float cos_theta_i, float cos_theta_t, const FloatOrColor& eta_i, const FloatOrColor& eta_t)
    {
      auto r_parallel = ((eta_t * cos_theta_i) - (eta_i * cos_theta_t)) /
                        ((eta_t * cos_theta_i) + (eta_i * cos_theta_t));

      auto r_perpendicular = ((eta_i * cos_theta_i) - (eta_t * cos_theta_t)) /
                             ((eta_i * cos_theta_i) + (eta_t * cos_theta_t));

      return min(1.f, (r_parallel * r_parallel + r_perpendicular * r_perpendicular) / 2.f);
    }

    inline static color evaluate(float cos_theta_i, float eta_i, float eta_t)
    {
      // compute sin theta_t using Snell's Law
      float sin_theta_t = eta_i/eta_t * std::sqrt(std::max(0.f, 1.f - cos_theta_i*cos_theta_i));

      // handle total internal reflection
      if(sin_theta_t > 1.f) return color{1.f};

      float cos_theta_t = std::sqrt(std::max(0.f, 1.f - sin_theta_t*sin_theta_t));

      return evaluate(std::fabs(cos_theta_i), cos_theta_t, color{eta_i}, color{eta_t});
    }

    inline color operator()(float cos_theta_i) const
    {
      float eta_i = eta_i_, eta_t = eta_t_;

      // if the ray is exiting the interface, reinterpret the indices of refraction
      if(cos_theta_i <= 0) std::swap(eta_i, eta_t);

      return color(evaluate(cos_theta_i, eta_i, eta_t));
    }

  private:
    float eta_i_;
    float eta_t_;
};


class fresnel
{
  private:
    using variant_type = std::experimental::variant<fresnel_no_op, fresnel_conductor, fresnel_dielectric>;

  public:
    template<class Fresnel,
             class = typename std::enable_if<
               std::is_constructible<variant_type,Fresnel>::value
             >::type>
    inline fresnel(const Fresnel& other)
      : variant_(other)
    {}

  private:
    struct visitor
    {
      float cos_theta_i;

      template<class F>
      color operator()(const F& f) const
      {
        return f(cos_theta_i);
      }
    };

  public:
    color operator()(float cos_theta_i) const
    {
      visitor v{cos_theta_i};
      return std::experimental::visit(v, variant_);
    }

  private:
    variant_type variant_;
};


} // end igloo

