#include <igloo/shading/material.hpp>

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
  // XXX might prefer to return some sort of null function here that requires no storage
  return lambertian(color::black());
} // end material::evaluate_scattering()

scattering_distribution_function material::evaluate_emission(const differential_geometry& dg) const
{
  // XXX might prefer to return some sort of null function here that requires no storage
  return hemispherical_emission(color::black());
} // end material::evaluate_emission()


} // end igloo

