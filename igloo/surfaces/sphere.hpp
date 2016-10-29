#pragma once

#include <igloo/surfaces/surface.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/normal.hpp>
#include <igloo/geometry/triangle_mesh.hpp>
#include <igloo/geometry/ray.hpp>
#include <igloo/geometry/pi.hpp>
#include <igloo/utility/optional.hpp>
#include <tuple>

namespace igloo
{


class sphere : public surface
{
  public:
    /*! Creates a new sphere.
     *  \param c The coordinates of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(const point &c, float r);

    /*! Creates a new sphere.
     *  \param cx The x-coordinate of the center of the sphere.
     *  \param cy The y-coordinate of the center of the sphere.
     *  \param cz The z-coordinate of the center of the sphere.
     *  \param r The radius of the sphere.
     */
    sphere(float cx, float cy, float cz, float r); 

    /*! \return The center of the sphere.
     */
    inline const point &center() const
    {
      return m_center;
    } // end sphere::center()

    /*! \return The radius of the sphere.
     */
    inline float radius() const
    {
      return m_radius;
    } // end sphere::radius()

    /*! \return A triangle_mesh approximating this sphere.
     */
    virtual triangle_mesh triangulate() const;

    /*! Tests for intersection between a ray and this sphere.
     *  \param r The ray of interest.
     *  \param nullopt if no intersection exists, otherwise the details of the intersection.
     */
    virtual optional<intersection> intersect(const ray &r) const;

    /*! \return The surface area of this sphere.
     */
    virtual float area() const;

    /*! \return The differential_geometry of the sphere at coordinates (u0,u1).
     */
    virtual differential_geometry sample_surface(std::uint64_t u0, std::uint64_t u1) const;

  private:
    static std::pair<float,float> solve_quadratic(float a, float b, float c);
    static parametric parametric_coordinates_at(const normal& n);

    // returns (uv, dpdu, dpdv) at the point p on the sphere with normal n
    std::tuple<parametric,vector,vector> parametric_geometry_at(const point& p, const normal& n) const;

    point m_center;
    float m_radius;

    static constexpr float max_phi = two_pi;
    static constexpr float min_theta = 0;
    static constexpr float max_theta = pi;
}; // end sphere


} // end igloo

