#include <igloo/materials/material.hpp>
#include <igloo/geometry/differential_geometry.hpp>

namespace igloo
{


class default_material : public registered_material<default_material>
{
  public:
    default_material() = default;

    // any parameters are ignored
    inline default_material(const std::map<std::string,any>&)
      : default_material()
    {}

    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;
}; // end default_material


} // end igloo

