#pragma once

#include <igloo/utility/math_vector.hpp>

namespace igloo
{


/*! A parametric represents parametric coordinates in the plane.
 */
class parametric : float2
{
  private:
    typedef float2 super_t;

  public:
    /*! Creates a new default constructed parametric.
     */
    inline parametric() : super_t() {}

    /*! Creates a new normal from a float2.
     *  \param v The float2 to copy.
     */
    inline parametric(const float2 &v) : super_t(v) {}

    /*! Creates a new parametric.
     *  \param val The x & y coordinate of the parametric coordinates.
     */
    inline parametric(float val) : super_t(val) {}

    /*! Creates a new parametric.
     *  \param x The x coordinate of the parametric coordinates.
     *  \param y The y coordinate of the parametric coordinates.
     */
    inline parametric(float x, float y) : super_t(x,y) {}

    /*! parametric difference.
     *  \param rhs The parametric to subtract.
     *  \return The parametric resulting from the given subtraction.
     */
    inline parametric operator-(const parametric &rhs) const
    {
      return as_float2() - rhs;
    } // end operator-()

    /*! parametric addition.
     *  \param rhs The parametric to add.
     *  \return The parametric resulting from the given addition.
     */
    inline parametric operator+(const parametric &rhs) const
    {
      return as_float2() + rhs;
    } // end operator+()

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;

  private:
    inline const float2 &as_float2() const
    {
      return *this;
    } // end as_float2()
}; // end parametric


/*! parametric scalar multiply.
 *  \param x The scalar to multiply by.
 *  \param p The parametric to scale.
 *  \return p multiplied by x.
 */
inline parametric operator*(float x, const parametric &p)
{
  return parametric(x * p.x, x * p.y);
} // end operator*()


} // end igloo

