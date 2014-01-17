#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


class spectrum : public detail::vector_base<spectrum, float, 3>
{
  private:
    typedef detail::vector_base<spectrum, float, 3> super_t;

  public:
    inline spectrum() : super_t() {}

    inline spectrum(float rr, float gg, float bb)
      : super_t(),
        r(rr),
        g(gg),
        b(bb)
    {}

    inline static spectrum black()
    {
      return spectrum(0,0,0);
    } // end black()

    inline static spectrum blue()
    {
      return spectrum(0,0,1);
    } // end red()

    inline static spectrum green()
    {
      return spectrum(0,1,0);
    } // end red()

    inline static spectrum cyan()
    {
      return spectrum(0,1,1);
    } // end red()

    inline static spectrum red()
    {
      return spectrum(1,0,0);
    } // end red()

    inline static spectrum violet()
    {
      return spectrum(1,0,1);
    } // end red()

    inline static spectrum yellow()
    {
      return spectrum(1,1,0);
    } // end red()

    inline static spectrum white()
    {
      return spectrum(1,1,1);
    } // end black()

    float r, g, b;
}; // end spectrum


} // end igloo

