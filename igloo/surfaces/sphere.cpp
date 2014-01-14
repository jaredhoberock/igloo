#include <igloo/surfaces/sphere.hpp>
#include <dependencies/2dmapping/UnitSquareToSphere.h>
#include <vector>
#include <algorithm>

namespace igloo
{


sphere::sphere(const point &c, float r)
  : m_center(c), m_radius(r)
{} // end sphere::sphere()


sphere::sphere(float cx, float cy, float cz, float r)
  : sphere(point(cx,cy,cz), r)
{} // end sphere::sphere()


triangle_mesh sphere::triangulate() const
{
  size_t u_divisions = 100;
  size_t v_divisions = 100;
  float u_del = 1.0f / u_divisions;
  float v_del = 1.0f / v_divisions;

  size_t num_vertices = 4 * u_divisions * v_divisions;

  std::vector<point>                   points(num_vertices);
  std::vector<parametric>              parametrics(num_vertices);
  std::vector<normal>                  normals(num_vertices);
  std::vector<triangle_mesh::triangle> triangles(2 * u_divisions * v_divisions);

  // XXX this method creates lots of redundant data
  // XXX we should try to make this watertight
  point p;
  float v = 0;
  unsigned int vertex_idx = 0;
  for(size_t j = 0; j != u_divisions; ++j, v += v_del)
  {
    float u = 0;
    for(size_t i = 0; i != v_divisions; ++i, u += u_del, vertex_idx += 4)
    {
      UnitSquareToSphere::evaluate(u, v, p);
      points[vertex_idx + 0]      = p;
      parametrics[vertex_idx + 0] = parametric(u,v);
      normals[vertex_idx + 0]     = normal(p.x, p.y, p.z);

      UnitSquareToSphere::evaluate(u + u_del, v, p);
      points[vertex_idx + 1]      = p;
      parametrics[vertex_idx + 1] = parametric(u + u_del,v);
      normals[vertex_idx + 1]     = normal(p.x, p.y, p.z);

      UnitSquareToSphere::evaluate(u + u_del, v + v_del, p);
      points[vertex_idx + 2]      = p;
      parametrics[vertex_idx + 2] = parametric(u + u_del, v + v_del);
      normals[vertex_idx + 2]     = normal(p.x, p.y, p.z);

      UnitSquareToSphere::evaluate(u, v + v_del, p);
      points[vertex_idx + 3]      = p;
      parametrics[vertex_idx + 3] = parametric(u,v + v_del);
      normals[vertex_idx + 3]     = normal(p.x, p.y, p.z);

      triangles[vertex_idx / 2]     = {vertex_idx + 0, vertex_idx + 1, vertex_idx + 2};
      triangles[vertex_idx / 2 + 1] = {vertex_idx + 0, vertex_idx + 2, vertex_idx + 3};
    } // end for
  } // end for j

  // scale each point by radius and translate each point by center
  float scale = radius();
  float3 translation = center().as_translation();
  std::transform(points.begin(), points.end(), points.begin(), [=](const point &x)
  {
    return (scale * x) + translation;
  });

  return triangle_mesh(points.begin(), points.end(),
                       parametrics.begin(),
                       normals.begin(),
                       triangles.begin(), triangles.end());
} // end triangulate::triangulate()


} // end igloo

