#include <igloo/materials/glass.hpp>

namespace igloo
{


const char* glass::name() const
{
  return "glass";
}

scattering_distribution_function glass::evaluate_scattering(const differential_geometry&) const
{
  return bsdf_;
}


} // end igloo

