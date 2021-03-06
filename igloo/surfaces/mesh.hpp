#pragma once

#include <igloo/surfaces/surface.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>
#include <igloo/geometry/triangle_mesh.hpp>
#include <igloo/utility/optional.hpp>
#include <igloo/utility/alias_table.hpp>

namespace igloo
{


class mesh : public surface
{
  public:
    /*! Creates a new mesh from an array of points and triangles.
     *  \param points An array of points.
     *  \param triangles An array of triangles.
     */
    mesh(const std::vector<point> &points,
         const std::vector<uint3> &triangles);

    /*! Creates a new mesh from an array of points, parametrics, and triangles.
     *  \param points An array of points.
     *  \param parametrics An array of parametric coordinates.
     *  \param num_vertices The size of the points and parametrics arrays.
     *  \param triangles An array of triangles.
     *  \param num_triangles The size of the triangles array.
     */
    mesh(const std::vector<point> &points,
         const std::vector<parametric> &parametrics,
         const std::vector<uint3> &triangles);

    /*! Creates a new mesh from an array of points, parametrics, normals, and triangles.
     *  \param points An array of points.
     *  \param parametrics An array of parametric coordinates.
     *  \param normals An array of normals.
     *  \param num_vertices The size of the points and parametrics arrays.
     *  \param triangles An array of triangles.
     *  \param num_triangles The size of the triangles array.
     */
    mesh(const std::vector<point> &points,
         const std::vector<parametric> &parametrics,
         const std::vector<normal> &normals,
         const std::vector<uint3> &triangles);

    /*! \return A triangle_mesh approximating this mesh.
     */
    inline virtual triangle_mesh triangulate() const
    {
      return m_triangle_mesh;
    } // end triangulate()

    /*! Tests for intersection between a ray and this mesh.
     *  \param r The ray of interest.
     *  \param nullopt if no intersection exists, otherwise the details of the intersection.
     */
    virtual optional<intersection> intersect(const ray &r) const;

    /*! \return The surface area of this mesh.
     */
    virtual float area() const;

    /*! \return The differential_geometry of the mesh at coordinates (u0,u1).
     */
    virtual differential_geometry sample_surface(std::uint64_t u0, std::uint64_t u1) const;

  private:
    mesh(triangle_mesh&& triangle_mesh);

    triangle_mesh m_triangle_mesh;
    alias_table<triangle_mesh::triangle_iterator> area_weighted_probability_density_function_;

    float area_;
}; // end mesh


} // end igloo

