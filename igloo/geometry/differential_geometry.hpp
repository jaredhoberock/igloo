#pragma once

#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class differential_geometry
{
  public:
    inline differential_geometry(const igloo::point& p, const parametric& uv, const vector& dpdu, const vector& dpdv, const normal& n)
      : point_(p),
        parametric_coordinates_(uv),
        dpdu_(dpdu),
        dpdv_(dpdv),
        normal_(n)
    {}

    inline const igloo::point& point() const
    {
      return point_;
    }

    inline const igloo::parametric& parametric_coordinates() const
    {
      return parametric_coordinates_;
    }

    inline const igloo::normal& normal() const
    {
      return normal_;
    }

    inline const igloo::vector& dpdu() const
    {
      return dpdu_;
    }

    inline const igloo::vector& dpdv() const
    {
      return dpdv_;
    }

    inline vector localize(const vector& v) const
    {
      return vector(dot(v,dpdu()), dot(v,dpdv()), dot(v, normal()));
    }

    inline float abs_cos_theta(const vector& w_local) const
    {
      return std::abs(w_local.z);
    }

  private:
    igloo::point  point_;
    parametric    parametric_coordinates_;
    vector        dpdu_;
    vector        dpdv_;
    igloo::normal normal_;
};


inline float distance(const differential_geometry& a, const differential_geometry& b)
{
  return distance(a.point(), b.point());
}


inline float distance_squared(const differential_geometry& a, const differential_geometry& b)
{
  return distance_squared(a.point(), b.point());
}


} // end igloo

