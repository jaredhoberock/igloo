#include <igloo/materials/material.hpp>
#include <igloo/scattering/color.hpp>
#include <igloo/scattering/hemispherical_emission.hpp>

namespace igloo
{


class light : public material
{
  public:
    // \param radiosity The radiosity of the light (i.e., power/area or Watts/meter^2)
    light(const color& radiosity);

    light(float r, float g, float b);

    virtual const char* name() const;

    virtual bool is_emitter() const;

    virtual scattering_distribution_function evaluate_emission(const differential_geometry& dg) const;

  private:
    hemispherical_emission emission_;
};


} // end igloo

