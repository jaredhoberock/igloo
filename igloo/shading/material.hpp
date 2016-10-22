#pragma once

#include <igloo/geometry/normal.hpp>
#include <igloo/shading/scattering_distribution_function.hpp>

namespace igloo
{


class material
{
  public:
    /*! \return A string containing the name of this material.
     */
    virtual const char *name() const = 0;

    /*! \return true if this material is emissive; false, otherwise.
     */
    virtual bool is_emitter() const;

    /*! \return true if this material is a sensor; false, otherwise.
     */
    virtual bool is_sensor() const;

    virtual scattering_distribution_function evaluate_scattering(const normal& ng) const = 0;

    virtual scattering_distribution_function evaluate_emission(const normal& ng) const = 0;
}; // end material


} // end igloo

