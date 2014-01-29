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


} // end igloo

