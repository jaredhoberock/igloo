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


struct area_of_triangle
{
  const triangle_mesh& self;

  float operator()(const triangle_mesh::triangle& tri) const
  {
    return self.surface_area(tri);
  }
};


mesh::mesh(triangle_mesh&& triangle_mesh)
  : m_triangle_mesh(std::move(triangle_mesh)),
    area_weighted_probability_density_function_(m_triangle_mesh.triangles(), area_of_triangle{m_triangle_mesh})
{} 


mesh::mesh(const std::vector<point> &points,
           const std::vector<uint3> &triangles)
  : mesh(triangle_mesh(points, triangles, face_normals(points, triangles)))
{}


mesh::mesh(const std::vector<point> &points,
           const std::vector<parametric> &parametrics,
           const std::vector<uint3> &triangles)
  : mesh(triangle_mesh(points, parametrics, triangles, face_normals(points, triangles)))
{}


mesh::mesh(const std::vector<point> &points,
           const std::vector<parametric> &parametrics,
           const std::vector<normal> &normals,
           const std::vector<uint3> &triangles)
  : mesh(triangle_mesh(points, parametrics, normals, triangles))
{}


optional<intersection>
  mesh::intersect(const ray &r) const
{
  auto hit = m_triangle_mesh.intersect(r); 
  if(hit)
  {
    triangle_mesh::triangle_iterator tri;
    float t;
    triangle_mesh::barycentric b;
    std::tie(tri, t, b) = *hit;

    parametric parm = m_triangle_mesh.parametric_at(tri, b);
    normal n = m_triangle_mesh.normal_at(tri, b);

    vector dpdu, dpdv;
    std::tie(dpdu, dpdv) = m_triangle_mesh.parameteric_derivatives(tri);

    return intersection(t, differential_geometry(r(t), parm, dpdu, dpdv, n));
  } // end if

  return nullopt;
} // end mesh::intersect()


float mesh::area() const
{
  return m_triangle_mesh.surface_area();
} // end mesh::area()


static std::uint8_t most_significant_byte(std::uint64_t x)
{
  return static_cast<std::uint8_t>(x >> (64 - 8));
}


differential_geometry mesh::sample_surface(float u0, float u1, float u2) const
{
  // select a triangle
  auto triangle_and_probability = area_weighted_probability_density_function_(u0);

  // XXX u1 and u2 are not barycentric coordinates, so this use is incorrect
  //     we need to transform from the unit square to the unit triangle first
  triangle_mesh::barycentric barycentric_coordinates(u1, u2);

  // select a point on the surface of the triangle
  auto p = m_triangle_mesh.point_at(triangle_and_probability.first, barycentric_coordinates);

  // get the normal there as well
  auto n = m_triangle_mesh.normal_at(triangle_and_probability.first, barycentric_coordinates);

  // XXX need to generate parametric, dpdu, and dpdv
  return differential_geometry(p, parametric(0), vector(0), vector(0), n);
} // end mesh::area()


} // end igloo

