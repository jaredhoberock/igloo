#pragma once

#include <igloo/utility/math_vector.hpp>
#include <igloo/utility/clamp.hpp>
#include <type_traits>
#include <cmath>

namespace igloo
{


class color : public math_vector_facade<color, float, 3>
{
  private:
    typedef math_vector_facade<color, float, 3> super_t;

  public:
    inline color() : super_t() {}

    template<typename OtherVector>
    color(const OtherVector &other,
          typename std::enable_if<
            !std::is_arithmetic<OtherVector>::value
          >::type * = 0) : super_t(other) {}

    template<typename Number>
    explicit color(Number v,
                   typename std::enable_if<
                     std::is_arithmetic<Number>::value
                   >::type * = 0) : super_t(v) {}

    inline color(float rr, float gg, float bb)
      : super_t(),
        r(rr),
        g(gg),
        b(bb)
    {}

    inline color abs() const
    {
      return color(std::abs(r), std::abs(g), std::abs(b));
    } // end abs()

    inline static color black()
    {
      return color(0,0,0);
    } // end black()

    inline static color blue()
    {
      return color(0,0,1);
    } // end red()

    inline static color green()
    {
      return color(0,1,0);
    } // end red()

    inline static color cyan()
    {
      return color(0,1,1);
    } // end red()

    inline static color red()
    {
      return color(1,0,0);
    } // end red()

    inline static color violet()
    {
      return color(1,0,1);
    } // end red()

    inline static color yellow()
    {
      return color(1,1,0);
    } // end red()

    inline static color white()
    {
      return color(1,1,1);
    } // end black()

    float r, g, b;
}; // end color


inline color operator-(const float a, const color& b)
{
  return color{a - b[0], a - b[1], a - b[2]};
}


template<class Number,
         class = typename std::enable_if<
           std::is_arithmetic<Number>::value
         >::type>
inline color operator/(const color& a, const Number& b)
{
  return color{a[0] / b, a[1] / b, a[2] / b};
}


inline color abs(const color &c)
{
  return c.abs();
}


inline color clamp(const color& c, float low, float high)
{
  return color{clamp(c[0], low, high), clamp(c[1], low, high), clamp(c[2], low, high)};
}


inline color sqrt(const color& c)
{
  return color{std::sqrt(c[0]), std::sqrt(c[1]), std::sqrt(c[2])};
}


inline color saturate(const color& c)
{
  return clamp(c, 0.f, 1.f);
}


template<class Number,
         class = typename std::enable_if<
           std::is_arithmetic<Number>::value
         >::type>
inline color min(const color& a, const Number& b)
{
  return color{std::min(a[0], b), std::min(a[1], b), std::min(a[2], b)};
}


template<class Number,
         class = typename std::enable_if<
           std::is_arithmetic<Number>::value
         >::type>
inline color min(const Number& a, const color& b)
{
  return color{std::min(a, b[0]), std::min(a, b[1]), std::min(a, b[2])};
}


} // end igloo

