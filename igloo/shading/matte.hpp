#include <igloo/shading/material.hpp>
#include <igloo/shading/color.hpp>
#include <igloo/shading/lambertian.hpp>

namespace igloo
{


class matte : public material
{
  public:
    matte(const color& c);

    matte(float r, float g, float b);

    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const normal &ng) const;

  private:
    const lambertian color_;
}; // end default_material


} // end igloo

