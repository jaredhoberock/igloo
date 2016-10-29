#include <igloo/viewers/scene_viewer.hpp>
#include <dependencies/glutviewer/GlutViewerInstance.h>
#include <igloo/geometry/triangle_mesh.hpp>
#include <iostream>
#include <algorithm>

namespace igloo
{


scene_viewer::scene_viewer(const scene &s,
                           const float4x4 &modelview)
  : m_scene(s),
    m_modelview(modelview)
{
  resize(512, 512);
  startAnimation();
}


void draw_mesh(const triangle_mesh &mesh)
{
  const point *points                      = mesh.points_data();
  const parametric *parametrics            = mesh.parametrics_data();
  const normal *normals                    = mesh.normals_data();

  glBegin(GL_TRIANGLES);
  if(mesh.has_vertex_normals())
  {
    for(const triangle_mesh::triangle& tri : mesh.triangles())
    {
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
        i != mesh.triangles().size();
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

  std::for_each(m_scene.begin(), m_scene.end(), [&](const surface_primitive &s)
  {
    glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT);

    // color lights yellow and turn off lighting
    if(s.material().is_emitter())
    {
      glDisable(GL_LIGHTING);
      glColor3f(1,1,0);
    }

    draw_mesh(s.triangulate());

    glPopAttrib();
  });

  glPopMatrix();
} // end draw()


} // end igloo

