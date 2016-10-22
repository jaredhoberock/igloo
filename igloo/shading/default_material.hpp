#include <igloo/shading/material.hpp>
#include <igloo/geometry/differential_geometry.hpp>

namespace igloo
{


class default_material : public material
{
  public:
    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

    virtual scattering_distribution_function evaluate_emission(const differential_geometry& dg) const;
}; // end default_material


} // end igloo

