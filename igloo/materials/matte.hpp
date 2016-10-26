#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/lambertian.hpp>

namespace igloo
{


class matte : public material
{
  public:
    matte(const color& c);

    matte(float r, float g, float b);

    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const differential_geometry& dg) const;

  private:
    const lambertian color_;
}; // end default_material


} // end igloo

