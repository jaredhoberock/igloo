#pragma once

#include <igloo/geometry/differential_geometry.hpp>

namespace igloo
{


class intersection
{
  public:
    inline intersection(float ray_parameter, const differential_geometry& dg)
      : ray_parameter_(ray_parameter),
        differential_geometry_(dg)
    {}

    inline float ray_parameter() const
    {
      return ray_parameter_;
    }

    const igloo::differential_geometry& differential_geometry() const
    {
      return differential_geometry_;
    }

  private:
    float ray_parameter_;
    igloo::differential_geometry differential_geometry_;
};


} // end igloo

