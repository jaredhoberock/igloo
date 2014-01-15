#include <igloo/igloo.hpp>
#include <igloo/viewers/test_viewer.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

namespace igloo
{


igloo::igloo()
  : m_transform_stack(std::deque<transform>(1))
{}


void igloo::translate(float tx, float ty, float tz)
{
  mult_matrix_(transform::translate(tx,ty,tz));
} // end igloo::translate()


void igloo::rotate(float degrees, float rx, float ry, float rz)
{
  mult_matrix_(transform::rotate(degrees, rx, ry, rz));
} // end igloo::rotate()


void igloo::scale(float sx, float sy, float sz)
{
  mult_matrix_(transform::scale(sx, sy, sz)); 
} // end igloo::scale();


void igloo::push_matrix()
{
  m_transform_stack.push(m_transform_stack.top());
} // end push_matrix()


void igloo::pop_matrix()
{
  m_transform_stack.pop();
} // end pop_matrix()


void igloo::mult_matrix(const float *m_)
{
  const float4x4 &m = *reinterpret_cast<const float4x4*>(m_);
  transform xfrm(m);

  mult_matrix_(xfrm);
} // end mult_matrix()


void igloo::mult_matrix_(const transform &xfrm)
{
  m_transform_stack.top() *= xfrm;
} // end mult_matrix_()


void igloo::sphere(float cx, float cy, float cz, float radius)
{
  typedef ::igloo::sphere sphere_type;

  // XXX should we scale the radius as well? not really clear how to do so
  point center = m_transform_stack.top()(point(cx,cy,cz));

  m_spheres.emplace_back(center,radius);
} // end igloo::sphere()


void igloo::mesh(const float *vertices_,
                 size_t num_vertices,
                 const unsigned int *triangles_,
                 size_t num_triangles)
{
  // XXX do we need to reverse the winding of vertices?

  std::vector<point> vertices(reinterpret_cast<const point*>(vertices_),
                              reinterpret_cast<const point*>(vertices_) + num_vertices);
  std::vector<uint3> triangles(reinterpret_cast<const uint3*>(triangles_),
                              reinterpret_cast<const uint3*>(triangles_) + num_triangles);

  std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](const point &p)
  {
    return m_transform_stack.top()(p);
  });

  m_meshes.emplace_back(vertices, triangles);
} // end igloo::mesh()


void igloo::mesh(const float *vertices_,
                 const float *parametrics_,
                 size_t num_vertices,
                 const unsigned int *triangles_,
                 size_t num_triangles)
{
  // XXX do we need to reverse the winding of vertices?

  std::vector<point> vertices(reinterpret_cast<const point*>(vertices_),
                              reinterpret_cast<const point*>(vertices_) + num_vertices);
  std::vector<parametric> parametrics(reinterpret_cast<const parametric*>(parametrics_),
                                      reinterpret_cast<const parametric*>(parametrics_) + num_vertices);
  std::vector<uint3> triangles(reinterpret_cast<const uint3*>(triangles_),
                               reinterpret_cast<const uint3*>(triangles_) + num_triangles);

  std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](const point &p)
  {
    return m_transform_stack.top()(p);
  });

  m_meshes.emplace_back(vertices, parametrics, triangles);
} // end igloo::mesh()

       
void igloo::mesh(const float *vertices_,
                 const float *parametrics_,
                 const float *normals_,
                 size_t num_vertices,
                 const unsigned int *triangles_,
                 size_t num_triangles)
{
  // XXX do we need to reverse the winding of vertices?

  std::vector<point> vertices(reinterpret_cast<const point*>(vertices_),
                              reinterpret_cast<const point*>(vertices_) + num_vertices);
  std::vector<parametric> parametrics(reinterpret_cast<const parametric*>(parametrics_),
                                      reinterpret_cast<const parametric*>(parametrics_) + num_vertices);
  std::vector<normal> normals(reinterpret_cast<const normal*>(normals_),
                              reinterpret_cast<const normal*>(normals_) + num_vertices);
  std::vector<uint3> triangles(reinterpret_cast<const uint3*>(triangles_),
                               reinterpret_cast<const uint3*>(triangles_) + num_triangles);

  std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](const point &p)
  {
    return m_transform_stack.top()(p);
  });

  std::transform(normals.begin(), normals.end(), normals.begin(), [&](const normal &n)
  {
    return m_transform_stack.top()(n);
  });

  m_meshes.emplace_back(vertices, parametrics, normals, triangles);
} // end igloo::mesh()


void igloo::render()
{
  float4x4 m(m_transform_stack.top().data());
  test_viewer v(m_spheres, m_meshes, m);
  v.setWindowTitle("Hello, world!");
  v.show();
} // end igloo::render()


} // end igloo

