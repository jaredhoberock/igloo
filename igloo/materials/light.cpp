#include <igloo/materials/light.hpp>
#include <igloo/scattering/hemispherical_emission.hpp>
#include <igloo/geometry/pi.hpp>

namespace igloo
{


light::light(const color& radiosity)
  : emission_(radiosity / pi) // convert radiosity (W * meter-2) to radiance (W * steradian-1 * meter-2)
{}

light::light(const std::map<std::string, any>& parameters)
  : light(std::experimental::fundamentals_v1::any_cast<color>(parameters.at("radiosity")))
{}

const char* light::name() const
{
  return "light";
}

bool light::is_emitter() const
{
  return true;
}

scattering_distribution_function light::evaluate_emission(const differential_geometry&) const
{
  return emission_;
}


} // end igloo

