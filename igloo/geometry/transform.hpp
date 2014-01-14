#pragma once

#include <igloo/geometry/matrix.hpp>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/point.hpp>

namespace igloo
{


class transform
{
  public:
    /*! Default constructor creates an identity transform.
     */
    transform();

    /*! Creates a new transform from a 4x4 matrix.
     *  \param m The matrix representing this transform.
     */
    transform(const float4x4 &m);

    /*! Creates a new transform from a 4x4 matrix.
     */
    transform(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33);

    /*! \return The inverse of this transform.
     */
    transform inverse() const;

    /*! \return A pointer to this transform's 4x4 row-major matrix data.
     */
    const float *data() const;

    /*! Multiplication operator returns the product of this transform with another.
     *  \param rhs The right hand side of the multiplication.
     *  \return The transform product (*this) * rhs.
     */
    transform operator*(const transform &rhs) const;

    /*! Multiplication-assign operator sets this transform to the product of this transform with another.
     *  \param rhs The right hand side of the multiplication.
     *  \return *this
     */
    transform &operator*=(const transform &rhs);

    /*! Transforms a point by applying this transform.
     *  \param p The point to transform.
     *  \return p transformed by *this.
     */
    point operator()(const point &p) const;

    /*! Transforms a point by applying this transform's inverse.
     *  \param p The point to transform.
     *  \return p transformed by this transform's inverse.
     */
    point inverse_transform(const point &p) const;

    /*! \return The identity transform.
     */
    static transform identity();

    /*! \param dx The x coordinate of the translation vector.
     *  \param dy The y coordinate of the translation vector.
     *  \param dz The z coordinate of the translation vector.
     *  \return The transform representing the translation (dx,dy,dz).
     */
    static transform translate(float dx, float dy, float dz);

    /*! \param degrees The size of the rotation, in degrees.
     *  \param rx The x coordinate of the rotation axis.
     *  \param ry The y coordinate of the rotation axis.
     *  \param rz The z coordinate of the rotation axis.
     *  \return The transform representing a degrees rotation about axis (rx, ry, rz).
     */
    static transform rotate(float degrees, float rx, float ry, float rz);

    /*! \param sx Magnitude of scaling in the x dimension.
     *  \param sy Magnitude of scaling in the y dimension.
     *  \param sz Magnitude of scaling in the z dimension.
     *  \return The transform representing a scaling of (sx, sy, sz).
     */
    static transform scale(float sx, float sy, float sz);

  private:
    transform(const float4x4 &xfrm, const float4x4 &inv);

    float4x4 m_xfrm, m_inv;
}; // end transform


} // end igloo

