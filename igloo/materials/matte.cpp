#include <igloo/materials/matte.hpp>
#include <igloo/scattering/hemispherical_emission.hpp>

namespace igloo
{


matte::matte(const color& c)
  : color_(c)
{}

matte::matte(float r, float g, float b)
  : matte(color(r,g,b))
{}

const char* matte::name() const
{
  return "matte";
}

scattering_distribution_function matte::evaluate_scattering(const differential_geometry&) const
{
  return color_;
}


} // end igloo

