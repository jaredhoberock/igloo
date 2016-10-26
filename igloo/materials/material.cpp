#include <iostream>
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


namespace detail
{


material_factories& get_material_factories()
{
  static material_factories factories;
  return factories;
}


std::unique_ptr<material> material_factories::make(const std::string& name, const std::map<std::string,any>& parameters) const
{
  assert(factories_.find(name) != factories_.end());
  return factories_.at(name)(parameters);
}


bool material_factories::register_material(const std::string& name, factory_type factory)
{
  factories_[name] = factory;
  return true;
}


} // end detail


std::unique_ptr<material> make_material(const std::string& name, const std::map<std::string,any>& parameters)
{
  return detail::get_material_factories().make(name, parameters);
}


} // end igloo

