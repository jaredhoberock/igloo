#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/lambertian.hpp>
#include <map>
#include <string>

namespace igloo
{


class matte : public registered_material<matte>
{
  public:
    matte(const color& albedo);

    matte(float r, float g, float b);

    matte(const std::map<std::string,any>& parameters);

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    const lambertian bsdf_;
}; // end default_material


} // end igloo

