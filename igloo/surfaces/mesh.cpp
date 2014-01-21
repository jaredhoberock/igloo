#include <igloo/surfaces/mesh.hpp>
#include <algorithm>

namespace igloo
{


static std::vector<normal> face_normals(const std::vector<point> &points,
                                        const std::vector<uint3> &triangles)
{
  std::vector<normal> result(triangles.size());

  std::transform(triangles.begin(), triangles.end(), result.begin(), [&](const uint3 &tri)
  {
    const point &v0 = points[tri[0]];
    const point &v1 = points[tri[1]];
    const point &v2 = points[tri[2]];

    return (v1 - v0).cross(v2 - v0).normalize();
  });

  return result;
} // end face_normals()


mesh::mesh(const std::vector<point> &points,
           const std::vector<uint3> &triangles)
  : m_triangle_mesh(points, triangles, face_normals(points, triangles))
{}


mesh::mesh(const std::vector<point> &points,
           const std::vector<parametric> &parametrics,
           const std::vector<uint3> &triangles)
  : m_triangle_mesh(points, parametrics, triangles, face_normals(points, triangles))
{}


mesh::mesh(const std::vector<point> &points,
           const std::vector<parametric> &parametrics,
           const std::vector<normal> &normals,
           const std::vector<uint3> &triangles)
  : m_triangle_mesh(points, parametrics, normals, triangles)
{}


bool mesh::intersect(const ray &r, float &t, normal &n) const
{
  auto result = m_triangle_mesh.intersect(r); 
  if(result)
  {
    triangle_mesh::triangle_iterator tri;
    triangle_mesh::barycentric b;
    std::tie(tri, t, b) = *result;

    n = m_triangle_mesh.normal_at(tri, b);
  } // end if

  return bool(result);
} // end mesh::intersect()


} // end igloo

