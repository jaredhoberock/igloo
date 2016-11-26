#include <igloo/materials/glass.hpp>

namespace igloo
{

glass::glass(const color& reflectance, 
             const color& transmittance,
             float eta)
  : bsdf_(reflectance, transmittance, 1.f, eta)
{}


glass::glass(const std::map<std::string,any>& parameters)
  : glass(std::experimental::fundamentals_v1::any_cast<color>(parameters.at("reflectance")),
          std::experimental::fundamentals_v1::any_cast<color>(parameters.at("transmittance")),
          std::experimental::fundamentals_v1::any_cast<float>(parameters.at("eta")))
{}

scattering_distribution_function glass::evaluate_scattering(const differential_geometry&) const
{
  return bsdf_;
}


} // end igloo

