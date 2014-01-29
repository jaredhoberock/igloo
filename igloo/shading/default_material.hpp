#include <igloo/shading/material.hpp>

namespace igloo
{


class default_material : public material
{
  public:
    virtual const char *name() const;

    virtual scattering_distribution_function evaluate_scattering(const normal &ng) const;
}; // end default_material


} // end igloo

