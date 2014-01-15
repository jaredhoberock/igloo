#pragma once

#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>
#include <igloo/geometry/transform.hpp>
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

    /*! Pushes a copy of the current matrix to the top of the matrix stack.
     */
    void push_matrix();

    /*! Pops the top of the matrix stack.
     */
    void pop_matrix();

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
    void sphere(float cx, float cy, float cz, float radius);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices.
     *  \param num_vertices The size of the vertices array.
     *  \param triangles An array of vertex index triples.
     *  \param num_triangles THe size of the triangles array.
     */
    void mesh(const float *vertices,
              size_t num_vertices,
              const unsigned int *triangles,
              size_t num_triangles);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices.
     *  \param parametrics An array of parametric triangle vertex positions.
     *  \param num_vertices The size of the vertices array.
     *  \param triangles An array of vertex index triples.
     *  \param num_triangles THe size of the triangles array.
     */
    void mesh(const float *vertices,
              const float *parametrics,
              size_t num_vertices,
              const unsigned int *triangles,
              size_t num_triangles);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices.
     *  \param parametrics An array of parametric triangle vertex positions.
     *  \param normals An array of vertex normals.
     *  \param num_vertices The size of the vertices array.
     *  \param triangles An array of vertex index triples.
     *  \param num_triangles THe size of the triangles array.
     */
    void mesh(const float *vertices,
              const float *parametrics,
              const float *normals,
              size_t num_vertices,
              const unsigned int *triangles,
              size_t num_triangles);

    /*! Starts a render.
     */
    void render();

  private:
    typedef ::igloo::sphere sphere_type; // disambiguate sphere the type from sphere the function
    std::vector<sphere_type> m_spheres;

    typedef ::igloo::mesh mesh_type; // disambiguate mesh the type from mesh the function
    std::vector<mesh_type> m_meshes;

    std::stack<transform> m_transform_stack;

    void mult_matrix_(const transform &xfrm);
};


} // end igloo

