#pragma once

#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class differential_geometry
{
  public:
    inline differential_geometry(const parametric& p, const normal& n)
      : parametric_coordinates_(p),
        normal_(n)
    {}

    const igloo::parametric& parametric_coordinates() const
    {
      return parametric_coordinates_;
    }

    const igloo::normal& normal() const
    {
      return normal_;
    }

  private:
    parametric parametric_coordinates_;
    igloo::normal normal_;
};


} // end igloo

