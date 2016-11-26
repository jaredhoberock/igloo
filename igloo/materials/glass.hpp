#pragma once

#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/perfect_glass.hpp>

namespace igloo
{


class glass : public registered_material<glass>
{
  public:
    glass(const color& reflectance = white,
          const color& tranmittance = white,
          float eta = 1.5f);

    glass(const std::map<std::string, any>& parameters);

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    perfect_glass bsdf_;
};


} // end igloo

