#pragma once

#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/specular_reflection.hpp>

namespace igloo
{


class glass : public registered_material<glass>
{
  public:
    inline glass(float eta = 1.5f,
                 const color& reflectance = color::white(),
                 const color& transmittance = color::white())
      : bsdf_(reflectance, transmittance, 1.f, eta)
    {}

    glass(const std::map<std::string, any>& parameters);

    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    specular_reflection bsdf_;
}; // end glass


} // end igloo

