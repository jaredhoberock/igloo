#pragma once

#include <igloo/surfaces/sphere.hpp>
#include <vector>

namespace igloo
{


class igloo
{
  public:
    /*! Creates a new sphere.
     *  \param cx The x-coordinate of the center of the Sphere.
     *  \param cy The y-coordinate of the center of the Sphere.
     *  \param cz The z-coordinate of the center of the Sphere.
     *  \param radius The radius of the Sphere.
     */
    virtual void sphere(float cx, float cy, float cz, float radius);

    /*! Starts a render.
     */
    virtual void render();

  private:
    typedef ::igloo::sphere sphere_type; // disambiguate sphere the type from sphere the function
    std::vector<sphere_type> m_spheres;
};


} // end igloo

