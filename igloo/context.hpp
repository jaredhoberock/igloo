#pragma once

#include <vector>
#include <stack>
#include <string>
#include <map>
#include <igloo/utility/array_ref.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/primitives/surface_primitive.hpp>
#include <igloo/geometry/transform.hpp>

namespace igloo
{


class context
{
  public:
    /*! Default constructs a new context.
     */
    context();
    
    /*! Pushes a copy of the current attributes to the top of the attributes stack.
     */
    void push_attributes();

    /*! Pops the top of the attributes stack.
     */
    void pop_attributes();

    /*! Sets the value of a named attribute.
     *  \param name The name of the attribute to set.
     *  \param val The value to set.
     *  XXX it would be cool to make the value of type boost::any
     */
    void attribute(const std::string &name, const std::string &val);

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

    /*! Creates a new sphere.
     *  \param cx The x-coordinate of the center of the Sphere.
     *  \param cy The y-coordinate of the center of the Sphere.
     *  \param cz The z-coordinate of the center of the Sphere.
     *  \param radius The radius of the Sphere.
     */
    void sphere(float cx, float cy, float cz, float radius);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices; size must be a multiple of 3.
     *  \param triangles An array of vertex index triples; size must be a multiple of 3.
     */
    void mesh(array_ref<const float> vertices, array_ref<const unsigned int> triangles);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices; vertices.size() must be a multiple of 3.
     *  \param parametrics An array of parametric triangle vertex positions; parametrics.size() must be a multiple of 2; parametrics.size() / 2 must equal size of vertices.size() / 3.
     *  \param triangles An array of vertex index triples; triangles.size() must be a multiple of 3.
     */
    void mesh(array_ref<const float> vertices,
              array_ref<const float> parametrics,
              array_ref<const unsigned int> triangles);

    /*! Creates a new mesh.
     *  \param vertices An array of triangle vertices; vertices.size() must be a multiple of 3.
     *  \param parametrics An array of parametric triangle vertex positions; parametric.size() must be a multiple of 2; parametrics.size() / 2 must equal size of vertices.size() / 3.
     *  \param normals An array of vertex normals; normals.size() must equal vertices.size().
     *  \param triangles An array of vertex index triples; triangles.size() must be a multiple of 3.
     */
    void mesh(array_ref<const float> vertices,
              array_ref<const float> parametrics,
              array_ref<const float> normals,
              array_ref<const unsigned int> triangles);

    /*! Introduces a new material and sets the current material to track this newly created material.
     *  \param m A material to take ownership of.
     *  \param name The of the material.
     */
    void material(std::unique_ptr<material>&& m, const std::string name);

    /*! Starts a render.
     */
    void render();

  private:
    void surface(std::unique_ptr<surface>&& surf);

    scene m_scene;

    std::stack<transform> m_transform_stack;

    typedef std::map<std::string,std::string> attributes_map;
    std::stack<attributes_map> m_attributes_stack;

    static attributes_map default_attributes();

    void mult_matrix_(const transform &xfrm);

    using materials_map = std::map<std::string, std::unique_ptr<igloo::material>>;
    materials_map m_materials;
}; // end context


} // end igloo

