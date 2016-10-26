#pragma once

#include <igloo/shading/color.hpp>

namespace igloo
{


class perfect_absorber
{
  public:
    inline color operator()(const vector&) const
    {
      return color::black();
    }

    inline color operator()(const vector&, const vector) const
    {
      return color::black();
    }
};


} // end igloo

