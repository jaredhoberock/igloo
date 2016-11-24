#include <igloo/materials/mirror.hpp>

namespace igloo
{

mirror::mirror(const color& reflectance, float eta)
  : bsdf_(reflectance, fresnel_conductor(approximate_absorption, reflectance, color(eta)))
{}


mirror::mirror(const std::map<std::string,any>& parameters)
  : mirror(std::experimental::fundamentals_v1::any_cast<color>(parameters.at("reflectance")),
           std::experimental::fundamentals_v1::any_cast<float>(parameters.at("eta")))
{}

scattering_distribution_function mirror::evaluate_scattering(const differential_geometry&) const
{
  return bsdf_;
}


} // end igloo

