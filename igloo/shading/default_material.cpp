#include <igloo/shading/default_material.hpp>

namespace igloo
{


const char *default_material::name() const
{
  return "default";
} // end default_material::name()


scattering_distribution_function default_material::evaluate_scattering(const differential_geometry&) const
{
  return lambertian(color(1));
} // end default_material::evaluate_scattering()


scattering_distribution_function default_material::evaluate_emission(const differential_geometry&) const
{
  return hemispherical_emission(color::black());
} // end default_material::evaluate_scattering()
  

} // end igloo

