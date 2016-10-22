#pragma once

#include <igloo/shading/color.hpp>

namespace igloo
{


class hemispherical_emission
{
  public:
    inline hemispherical_emission(const color& radiosity)
      : radiance_(radiosity / 3.14159265359f)
    {}

    inline color operator()(const vector& wo, const normal& n) const
    {
      // are wo and n in the same hemisphere?
      if(dot(wo,n) > 0)
      {
        return radiance_;
      }

      return color::black();
    }

    inline color operator()(const vector& wo, const normal& n, const vector&) const
    {
      return operator()(wo,n);
    }

  private:
    const color radiance_;
};


} // end igloo

