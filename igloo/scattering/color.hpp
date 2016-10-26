#pragma once

#include <igloo/utility/math_vector.hpp>
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


inline color abs(const color &c)
{
  return c.abs();
} // end abs()


} // end igloo

