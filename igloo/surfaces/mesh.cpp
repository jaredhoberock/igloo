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
    area_weighted_probability_density_function_(m_triangle_mesh.triangles(), area_of_triangle{m_triangle_mesh}),
    area_(m_triangle_mesh.surface_area())
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

    parametric uv = m_triangle_mesh.parametric_at(tri, b);
    normal n = m_triangle_mesh.normal_at(tri, b);

    vector dpdu, dpdv;
    std::tie(dpdu, dpdv) = m_triangle_mesh.parameteric_derivatives(tri);

    return intersection(t, differential_geometry(r(t), uv, dpdu, dpdv, n));
  } // end if

  return nullopt;
} // end mesh::intersect()


float mesh::area() const
{
  return area_;
} // end mesh::area()


static std::uint8_t most_significant_byte(std::uint64_t x)
{
  return static_cast<std::uint8_t>(x >> (64 - 8));
}


static triangle_mesh::barycentric unit_square_to_barycentric_coordinates(float u0, float u1)
{
  float su = std::sqrt(u0);
  return triangle_mesh::barycentric(1.f - su, u1 * su);
}


differential_geometry mesh::sample_surface(float u0, float u1, float u2) const
{
  // select a triangle
  auto triangle_and_probability = area_weighted_probability_density_function_(u0);

  // transform the unit square to barycentric coordinates
  auto barycentric_coordinates = unit_square_to_barycentric_coordinates(u1, u2);

  point p = m_triangle_mesh.point_at(triangle_and_probability.first, barycentric_coordinates);
  normal n = m_triangle_mesh.normal_at(triangle_and_probability.first, barycentric_coordinates);
  parametric uv = m_triangle_mesh.parametric_at(triangle_and_probability.first, barycentric_coordinates);

  // XXX need to generate dpdu and dpdv
  return differential_geometry(p, uv, vector(0), vector(0), n);
} // end mesh::area()


} // end igloo

