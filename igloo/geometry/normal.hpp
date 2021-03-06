#pragma once

#include <igloo/geometry/vector.hpp>

namespace igloo
{


/*! A normal represents a normal vector in 3-space.
 */
class normal : vector
{
  private:
    typedef vector super_t;

  public:
    /*! Creates a new default constructed normal.
     */
    inline normal() : super_t() {}

    /*! Creates a new normal from a vector.
     *  \param v The vector to copy.
     */
    inline normal(const vector &v) : super_t(v) {}

    /*! Creates a new normal.
     *  \param x The x coordinate of the normal.
     *  \param y The y coordinate of the normal.
     *  \param z The z coordinate of the normal.
     */
    inline normal(float x, float y, float z) : super_t(x,y,z) {}

    /*! normal difference.
     *  \param rhs The normal to subtract.
     *  \return The normal resulting from the given subtraction.
     */
    inline normal operator-(const normal &rhs) const
    {
      return as_vector() - rhs;
    } // end operator-()

    /*! normal addition.
     *  \param rhs The normal to add.
     *  \return The normal resulting from the given addition.
     */
    inline normal operator+(const normal &rhs) const
    {
      return as_vector() + rhs;
    } // end operator+()

    using super_t::operator[];
    using super_t::operator float *;
    using super_t::operator const float *;

    using super_t::x;
    using super_t::y;
    using super_t::z;

    friend inline vector cross(const normal &a, const normal &b)
    {
      return igloo::cross(a.as_vector(), b.as_vector());
    }

    friend inline vector cross(const normal& a, const vector& b)
    {
      return igloo::cross(a.as_vector(), b);
    }

    friend inline vector cross(const vector& a, const normal& b)
    {
      return igloo::cross(a, b.as_vector());
    }

    friend inline float dot(const normal &a, const normal &b)
    {
      return igloo::dot(a.as_vector(), b.as_vector());
    }

    friend inline float dot(const vector &a, const normal &b)
    {
      return igloo::dot(a, b.as_vector());
    }

    friend inline float dot(const normal &a, const vector &b)
    {
      return igloo::dot(a.as_vector(), b);
    }

    friend inline float abs_dot(const normal &a, const normal &b)
    {
      return igloo::abs_dot(a.as_vector(), b.as_vector());
    }

    friend inline float abs_dot(const vector &a, const normal &b)
    {
      return igloo::abs_dot(a, b.as_vector());
    }

    friend inline float abs_dot(const normal &a, const vector &b)
    {
      return igloo::abs_dot(a.as_vector(), b);
    }

    friend inline std::ostream& operator<<(std::ostream& os, const normal& n)
    {
      return os << n.as_vector();
    }

  private:
    inline const vector &as_vector() const
    {
      return *this;
    } // end as_vector()
}; // end normal


/*! normal scalar multiply.
 *  \param x The scalar to multiply by.
 *  \param n The normal to scale.
 *  \return n multiplied by x.
 */
inline vector operator*(float x, const normal &n)
{
  return vector(x * n.x, x * n.y, x * n.z);
} // end operator*()


} // end igloo


namespace std
{


template<std::size_t I>
struct tuple_element<I, igloo::normal>
{
  using type = float;
};


} // end std


