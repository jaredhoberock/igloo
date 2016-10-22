#include <igloo/shading/material.hpp>
#include <igloo/shading/color.hpp>
#include <igloo/shading/hemispherical_emission.hpp>

namespace igloo
{


class light : public material
{
  public:
    light(const color& radiosity);

    light(float r, float g, float b);

    virtual const char* name() const;

    virtual bool is_emitter() const;

    virtual scattering_distribution_function evaluate_scattering(const normal& ng) const;

    virtual scattering_distribution_function evaluate_emission(const normal& ng) const;

  private:
    hemispherical_emission emission_;
};


} // end igloo

