#include <igloo/shading/light.hpp>
#include <igloo/shading/hemispherical_emission.hpp>

namespace igloo
{


light::light(const color& radiosity)
  : emission_(radiosity)
{}

light::light(float r, float g, float b)
  : light(color(r,g,b))
{}

const char* light::name() const
{
  return "light";
}

bool light::is_emitter() const
{
  return true;
}

scattering_distribution_function light::evaluate_scattering(const differential_geometry&) const
{
  return lambertian(color::black());
}

scattering_distribution_function light::evaluate_emission(const differential_geometry&) const
{
  return emission_;
}


} // end igloo

