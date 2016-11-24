#pragma once

#include <igloo/scattering/color.hpp>
#include <igloo/utility/variant.hpp>


namespace igloo
{


class fresnel_no_op
{
  public:
    inline color operator()(const float) const
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

    inline static color evaluate(const float cosi, const color& eta, const color& k)
    {
      float c2 = cosi*cosi;
      color cosi2(c2, c2, c2);
      color tmp = cosi2 * (eta*eta + k*k);
      
      color r_parallel2 = (tmp - (2.f * eta * cosi) + color::white()) /
                          (tmp + (2.f * eta * cosi) + color::white());
      color tmp_f = eta*eta + k*k;
      
      color r_perp2 = (tmp_f - (2.f * eta * cosi) + cosi2) /
                      (tmp_f + (2.f * eta * cosi) + cosi2);
      
      return (r_parallel2 + r_perp2) / 2.f;
    }

    color operator()(const float cosi) const
    {
      return evaluate(std::fabs(cosi), eta_, k_);
    }

  private:
    color eta_;
    color k_;
};


class fresnel
{
  private:
    using variant_type = std::experimental::variant<fresnel_no_op, fresnel_conductor>;

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
      float cosi;

      template<class F>
      color operator()(const F& f) const
      {
        return f(cosi);
      }
    };

  public:
    color operator()(const float cosi) const
    {
      visitor v{cosi};
      return std::experimental::visit(v, variant_);
    }

  private:
    variant_type variant_;
};


} // end igloo

