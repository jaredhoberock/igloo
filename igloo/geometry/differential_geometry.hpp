#pragma once

#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class differential_geometry
{
  public:
    inline differential_geometry(const parametric& p, const vector& dpdu, const vector& dpdv, const normal& n)
      : parametric_coordinates_(p),
        dpdu_(dpdu),
        dpdv_(dpdv),
        normal_(n)
    {}

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
    parametric parametric_coordinates_;
    vector        dpdu_;
    vector        dpdv_;
    igloo::normal normal_;
};


} // end igloo

