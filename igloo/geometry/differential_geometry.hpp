#pragma once

#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class differential_geometry
{
  public:
    inline differential_geometry(const parametric& p, const normal& geometric_normal)
      : parametric_coordinates_(p),
        geometric_normal_(geometric_normal)
    {}

    const igloo::parametric& parametric_coordinates() const
    {
      return parametric_coordinates_;
    }

    const igloo::normal& geometric_normal() const
    {
      return geometric_normal_;
    }

  private:
    parametric parametric_coordinates_;
    normal     geometric_normal_;
};


} // end igloo

