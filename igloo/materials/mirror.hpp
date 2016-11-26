#pragma once

#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/specular_reflection.hpp>

namespace igloo
{


class mirror : public registered_material<mirror>
{
  public:
    mirror(const color& reflectance = white, float eta = 2.485f);

    mirror(const std::map<std::string, any>& parameters);

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    specular_reflection bsdf_;
}; // end mirror


} // end igloo

