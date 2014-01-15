#include <igloo/context.hpp>
#include <igloo/viewers/test_viewer.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

namespace igloo
{


context::context()
  : m_transform_stack(std::deque<transform>(1)),
    m_attributes_stack(std::deque<attributes_map>(1, default_attributes()))
{}


void context::push_matrix()
{
  m_transform_stack.push(m_transform_stack.top());
} // end context::push_matrix()


void context::pop_matrix()
{
  m_transform_stack.pop();
} // end context::pop_matrix()


void context::mult_matrix(const float *m_)
{
  const float4x4 &m = *reinterpret_cast<const float4x4*>(m_);
  transform xfrm(m);

  mult_matrix_(xfrm);
} // end context::mult_matrix()


void context::mult_matrix_(const transform &xfrm)
{
  m_transform_stack.top() *= xfrm;
} // end context::mult_matrix_()


void context::push_attributes()
{
  m_attributes_stack.push(m_attributes_stack.top());
} // end context::push_attributes()


void context::pop_attributes()
{
  m_attributes_stack.pop();
} // end context::pop_attributes()


void context::attribute(const std::string &name, const std::string &val)
{
  m_attributes_stack.top()[name] = val;
} // end context::attribute()


context::attributes_map context::default_attributes()
{
  return {
    {"record:width",  "512"},
    {"record:height", "512"},
    {"orientation", "outside"}
  };
} // end context::default_attributes()


void context::translate(float tx, float ty, float tz)
{
  mult_matrix_(transform::translate(tx,ty,tz));
} // end igloo::translate()


void context::rotate(float degrees, float rx, float ry, float rz)
{
  mult_matrix_(transform::rotate(degrees, rx, ry, rz));
} // end context::rotate()


void context::scale(float sx, float sy, float sz)
{
  mult_matrix_(transform::scale(sx, sy, sz)); 
} // end context::scale();


void context::sphere(float cx, float cy, float cz, float radius)
{
  // XXX should we scale the radius as well? not really clear how to do so
  point center = m_transform_stack.top()(point(cx,cy,cz));

  m_spheres.emplace_back(center,radius);
} // end context::sphere()


void context::mesh(const float *vertices_,
                   size_t num_vertices,
                   const unsigned int *triangles_,
                   size_t num_triangles)
{
  std::vector<point> vertices(reinterpret_cast<const point*>(vertices_),
                              reinterpret_cast<const point*>(vertices_) + num_vertices);
  std::vector<uint3> triangles(reinterpret_cast<const uint3*>(triangles_),
                               reinterpret_cast<const uint3*>(triangles_) + num_triangles);

  std::transform(vertices.begin(), vertices.end(), vertices.begin(), [&](const point &p)
  {
    return m_transform_stack.top()(p);
  });

  if(m_attributes_stack.top()["orientation"] == "inside")
  {
    std::transform(triangles.begin(), triangles.end(), triangles.begin(), [](const uint3 &tri)
    {
      return uint3(tri.x, tri.z, tri.y);
    });
  } // end if

  m_meshes.emplace_back(vertices, triangles);
} // end context::mesh()


void context::mesh(const float *vertices_,
                   const float *parametrics_,
                   size_t num_vertices,
                   const unsigned int *triangles_,
                   size_t num_triangles)
{
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

  // do we need to reverse the winding of vertices?
  if(m_attributes_stack.top()["orientation"] == "inside")
  {
    std::transform(triangles.begin(), triangles.end(), triangles.begin(), [](const uint3 &tri)
    {
      return uint3(tri.x, tri.z, tri.y);
    });
  } // end if

  m_meshes.emplace_back(vertices, parametrics, triangles);
} // end context::mesh()

       
void context::mesh(const float *vertices_,
                   const float *parametrics_,
                   const float *normals_,
                   size_t num_vertices,
                   const unsigned int *triangles_,
                   size_t num_triangles)
{
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

  // note that we don't reverse the direction of normals, even if orientation == inside
  std::transform(normals.begin(), normals.end(), normals.begin(), [&](const normal &n)
  {
    return m_transform_stack.top()(n);
  });

  // do we need to reverse the winding of vertices?
  if(m_attributes_stack.top()["orientation"] == "inside")
  {
    std::transform(triangles.begin(), triangles.end(), triangles.begin(), [](const uint3 &tri)
    {
      return uint3(tri.x, tri.z, tri.y);
    });
  } // end if

  m_meshes.emplace_back(vertices, parametrics, normals, triangles);
} // end context::mesh()


void context::render()
{
  int height = std::atoi(m_attributes_stack.top()["record:height"].c_str());
  int width  = std::atoi(m_attributes_stack.top()["record:width"].c_str());

  float4x4 m(m_transform_stack.top().data());
  test_viewer v(m_spheres, m_meshes, m);
  v.setWindowTitle("Hello, world!");
  v.camera()->setAspectRatio(float(width)/height);
  v.resize(width,height);
  v.show();
} // end context::render()


} // end igloo

