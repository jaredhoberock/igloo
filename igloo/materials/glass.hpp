#pragma once

#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/specular_transmission.hpp>

namespace igloo
{


class glass : public registered_material<glass>
{
  public:
    glass(const color& reflectance = color::white(),
          const color& tranmittance = color::white(),
          float eta = 1.5f);

    glass(const std::map<std::string, any>& parameters);

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    specular_transmission bsdf_;
}; // end glass


} // end igloo

