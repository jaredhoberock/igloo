#pragma once

#include <igloo/scattering/color.hpp>

namespace igloo
{


class perfect_absorber
{
  public:
    inline color operator()(const vector&) const
    {
      return black;
    }

    inline color operator()(const vector&, const vector) const
    {
      return black;
    }
};


} // end igloo

