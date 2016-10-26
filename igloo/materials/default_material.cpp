#include <igloo/materials/default_material.hpp>

namespace igloo
{


scattering_distribution_function default_material::evaluate_scattering(const differential_geometry&) const
{
  return lambertian(color(1));
} // end default_material::evaluate_scattering()
 

} // end igloo

