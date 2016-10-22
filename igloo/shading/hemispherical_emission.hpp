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

    inline color operator()(const vector& wo) const
    {
      // are we in the +z hemispher?
      if(wo.z > 0)
      {
        return radiance_;
      }

      return color::black();
    }

    inline color operator()(const vector& wo, const vector&) const
    {
      return operator()(wo);
    }

  private:
    const color radiance_;
};


} // end igloo

