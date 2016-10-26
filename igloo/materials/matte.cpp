#include <igloo/materials/matte.hpp>
#include <igloo/scattering/hemispherical_emission.hpp>

namespace igloo
{


matte::matte(const color& albedo)
  : bsdf_(albedo)
{}

matte::matte(float r, float g, float b)
  : matte(color(r,g,b))
{}

matte::matte(const std::map<std::string,any>& parameters)
  : matte(std::experimental::fundamentals_v1::any_cast<color>(parameters.at("albedo")))
{}

const char* matte::name() const
{
  return "matte";
}

scattering_distribution_function matte::evaluate_scattering(const differential_geometry&) const
{
  return bsdf_;
}


} // end igloo

