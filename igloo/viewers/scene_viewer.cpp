#include <igloo/viewers/scene_viewer.hpp>
#include <dependencies/glutviewer/GlutViewerInstance.h>
#include <dependencies/2dmapping/UnitSquareToSphere.h>
#include <igloo/geometry/triangle_mesh.hpp>
#include <iostream>
#include <algorithm>

namespace igloo
{


scene_viewer::scene_viewer(const std::vector<surface_primitive> &primitives,
                           const float4x4 &modelview)
  : m_surfaces(primitives),
    m_modelview(modelview)
{
  resize(512, 512);
}


void draw_mesh(const triangle_mesh &mesh)
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


void scene_viewer::draw()
{
  glPushMatrix();

  // invert m_modelview and send its transpose to GL
  // GL's matrix format is column-major

  glMultMatrixf(m_modelview.inverse().transpose());

  std::for_each(m_surfaces.begin(), m_surfaces.end(), [&](const surface_primitive &s)
  {
    draw_mesh(s.triangulate());
  });

  glPopMatrix();
} // end draw()


} // end igloo

