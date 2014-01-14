#pragma once

#include <igloo/surfaces/sphere.hpp>
#include <igloo/geometry/matrix.hpp>
#include <vector>
#include <stack>

namespace igloo
{


class igloo
{
  public:
    /*! Default constructs a new igloo.
     */
    igloo();

    /*! Transforms the top of the matrix stack by the given translation.
     *  \param tx The x coordinate of the translation vector.
     *  \param ty The y coordinate of the translation vector.
     *  \param tz The z coordinate of the translation vector.
     */
    void translate(float tx, float ty, float tz);

    /*! Transforms the top of the matrix stack by the given rotation.
     *  \param degrees The angle of rotation, in degrees.
     *  \param rx The x coordinate of the axis of rotation.
     *  \param ry The y coordinate of the axis of rotation.
     *  \param rz The z coordinate of the axis of rotation.
     */
    void rotate(float degrees, float rx, float ry, float rz);

    /*! Scales the top of the matrix stack by the given scale.
     *  \param sx The scale in the x dimension.
     *  \param sy The scale in the y dimension.
     *  \param sz The scale in the z dimension.
     */
    void scale(float sx, float sy, float sz);

    /*! Multiplies the top of the matrix stack by the given 4x4 matrix.
     *  \param m A row-major order 4x4 matrix.
     */
    void mult_matrix(const float *m);

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

    std::stack<float4x4> m_matrix_stack;
};


} // end igloo

