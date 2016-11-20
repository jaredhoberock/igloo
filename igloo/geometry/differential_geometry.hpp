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
        s_(normalize(dpdu)),
        t_(cross(n, s_)),
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

    inline const vector& s() const
    {
      return s_;
    }

    inline const vector& t() const
    {
      return s_;
    }

    inline const igloo::normal& normal() const
    {
      return normal_;
    }

    inline vector localize(const vector& v) const
    {
      return vector(dot(v,s_), dot(v,t_), dot(v, normal()));
    }

    inline vector globalize(const vector& v) const
    {
      // the matrix we multiply here is the transpose of the matrix of localize()
      return vector(s_[0] * v[0] + t_[0] * v[1] + normal_[0] * v[2],
                    s_[1] * v[0] + t_[1] * v[1] + normal_[1] * v[2],
                    s_[2] * v[0] + t_[2] * v[1] + normal_[2] * v[2]);
    }

    inline float abs_cos_theta(const vector& w_local) const
    {
      return std::abs(w_local.z);
    }

  private:
    igloo::point  point_;
    parametric    parametric_coordinates_;
    vector        s_;
    vector        t_;
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

