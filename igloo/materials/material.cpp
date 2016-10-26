#include <igloo/materials/material.hpp>
#include <igloo/scattering/perfect_absorber.hpp>

namespace igloo
{


bool material::is_emitter() const
{
  return false;
} // end material::is_emitter()


bool material::is_sensor() const
{
  return false;
} // end material::is_sensor()


scattering_distribution_function material::evaluate_scattering(const differential_geometry& dg) const
{
  return perfect_absorber();
} // end material::evaluate_scattering()

scattering_distribution_function material::evaluate_emission(const differential_geometry& dg) const
{
  return perfect_absorber();
} // end material::evaluate_emission()


} // end igloo

