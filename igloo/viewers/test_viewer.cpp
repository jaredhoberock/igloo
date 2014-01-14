#include <igloo/viewers/test_viewer.hpp>
#include <dependencies/glutviewer/GlutViewerInstance.h>
#include <dependencies/2dmapping/UnitSquareToSphere.h>
#include <igloo/geometry/triangle_mesh.hpp>
#include <iostream>

namespace igloo
{


test_viewer::test_viewer(const sphere &s, const float4x4 &modelview)
  : m_sphere(s),
    m_modelview(modelview)
{}


void draw(const triangle_mesh &mesh)
{
  const point *points                      = mesh.points_data();
  const parametric *parametrics            = mesh.parametrics_data();
  const normal *normals                    = mesh.normals_data();

  glBegin(GL_TRIANGLES);
  for(auto iter = mesh.triangles_begin();
      iter != mesh.triangles_end();
      ++iter)
  {
    const triangle_mesh::triangle &tri = *iter;

    glNormal3fv(normals[tri[0]]);
    glTexCoord2fv(parametrics[tri[0]]);
    glVertex3fv(points[tri[0]]);

    glNormal3fv(normals[tri[1]]);
    glTexCoord2fv(parametrics[tri[1]]);
    glVertex3fv(points[tri[1]]);

    glNormal3fv(normals[tri[2]]);
    glTexCoord2fv(parametrics[tri[2]]);
    glVertex3fv(points[tri[2]]);
  } // end for tri
  glEnd();
} // end draw()


void draw_sphere(const sphere &s)
{
  draw(s.triangulate());
} // end draw()


void test_viewer::draw()
{
  glPushMatrix();

  // invert m_modelview and send its transpose to GL
  // GL's matrix format is column-major

  glMultMatrixf(m_modelview.inverse().transpose());
  draw_sphere(m_sphere);

  glPopMatrix();
} // end draw()


} // end igloo

