#include <igloo/viewers/test_viewer.hpp>
#include <dependencies/glutviewer/GlutViewerInstance.h>
#include <dependencies/2dmapping/UnitSquareToSphere.h>
#include <igloo/geometry/triangle_mesh.hpp>
#include <iostream>
#include <algorithm>

namespace igloo
{


test_viewer::test_viewer(const std::vector<sphere> &spheres,
                         const std::vector<mesh> &meshes,
                         const float4x4 &modelview)
  : m_spheres(spheres),
    m_meshes(meshes),
    m_modelview(modelview)
{}


void draw(const triangle_mesh &mesh)
{
  const point *points                      = mesh.points_data();
  const parametric *parametrics            = mesh.parametrics_data();
  const normal *normals                    = mesh.normals_data();

  glBegin(GL_TRIANGLES);
  if(mesh.has_vertex_normals())
  {
    for(auto iter = mesh.triangles_begin();
        iter != mesh.triangles_end();
        ++iter)
    {
      const triangle_mesh::triangle &tri = *iter;

      glNormal3fv(normals[tri[0]]);
      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[0]]);
      }
      glVertex3fv(points[tri[0]]);

      glNormal3fv(normals[tri[1]]);
      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[1]]);
      }
      glVertex3fv(points[tri[1]]);

      glNormal3fv(normals[tri[2]]);
      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[2]]);
      }
      glVertex3fv(points[tri[2]]);
    } // end for tri
  } // end if
  else
  {
    for(size_t i = 0;
        i != mesh.triangles_size();
        ++i)
    {
      const triangle_mesh::triangle &tri = mesh.triangles_data()[i];

      if(mesh.has_normals())
      {
        glNormal3fv(mesh.normals_data()[i]);
      }

      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[0]]);
      }
      glVertex3fv(points[tri[0]]);

      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[1]]);
      }
      glVertex3fv(points[tri[1]]);

      if(mesh.has_parametrics())
      {
        glTexCoord2fv(parametrics[tri[2]]);
      }
      glVertex3fv(points[tri[2]]);
    } // end for tri
  } // end else
  glEnd();
} // end draw()


void draw_sphere(const sphere &s)
{
  draw(s.triangulate());
} // end draw()


void draw_mesh(const mesh &m)
{
  draw(m.triangulate());
} // end draw_mesh()


void test_viewer::draw()
{
  glPushMatrix();

  // invert m_modelview and send its transpose to GL
  // GL's matrix format is column-major

  glMultMatrixf(m_modelview.inverse().transpose());

  std::for_each(m_spheres.begin(), m_spheres.end(), [&](const sphere &s)
  {
    draw_sphere(s);
  });

  std::for_each(m_meshes.begin(), m_meshes.end(), [&](const mesh &m)
  {
    draw_mesh(m);
  });

  glPopMatrix();
} // end draw()


} // end igloo

