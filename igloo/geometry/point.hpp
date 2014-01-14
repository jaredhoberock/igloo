#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


/*! A point represents coordinates in 3-space.
 */
class point : float3
{
  private:
    typedef float3 super_t;

    /*! Creates a new point from a float3.
     *  \param v The float3 to copy.
     */
    inline point(const float3 &v) : super_t(v) {}

  public:
    /*! Creates a new default constructed point.
     */
    inline point() : super_t() {}

    /*! Creates a new point.
     *  \param x The x coordinate of the point.
     *  \param y The y coordinate of the point.
     *  \param z The z coordinate of the point.
     */
    inline point(float x, float y, float z) : super_t(x,y,z) {}

    /*! point difference.
     *  \param rhs The point to subtract.
     *  \return The vector pointing from rhs to *this.
     */
    inline float3 operator-(const point &rhs) const
    {
      return static_cast<const float3&>(*this) - rhs;
    } // end operator-()

    /*! \return the vector representing this point as a translation from the origin.
     */
    inline float3 as_translation() const
    {
      return (*this) - point(0,0,0);
    } // end as_translation()

    /*! Translation.
     *  \param rhs The vector to add.
     *  \return The point resulting from the given translation.
     */
    inline point operator+(const float3 &rhs) const
    {
      return static_cast<const float3&>(*this) + rhs;
    } // end operator+()

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;
    using super_t::z;
}; // end point


/*! Scalar multiply for points. 
 *  \param s Scale factor.
 *  \param x The point to scale.
 *  \return x scaled by s.
 */
inline point operator*(float s, const point &x)
{
  return point(s * x.x, s * x.y, s * x.z);
} // end operator*()


} // end igloo

