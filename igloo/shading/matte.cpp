#include <igloo/shading/matte.hpp>

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

scattering_distribution_function matte::evaluate_scattering(const normal& ng) const
{
  return color_;
}


} // end igloo

