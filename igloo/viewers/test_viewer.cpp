#include <igloo/viewers/test_viewer.hpp>
#include <dependencies/glutviewer/GlutViewerInstance.h>
#include <dependencies/2dmapping/UnitSquareToSphere.h>
#include <iostream>

namespace igloo
{


test_viewer::test_viewer(const sphere &s, const float4x4 &modelview)
  : m_sphere(s),
    m_modelview(modelview)
{}


void draw_sphere(const sphere &s)
{
  typedef float point_type[3];
  point_type c;
  std::tie(c[0],c[1],c[2]) = s.center();

  glPushAttrib(GL_POLYGON_BIT);
  glEnable(GL_CULL_FACE);

  // push the transform
  glPushMatrix();

  glTranslatef(c[0], c[1], c[2]);
  
  size_t uDivisions = 100;
  size_t vDivisions = 100;
  float uDel = 1.0f / uDivisions;
  float vDel = 1.0f / vDivisions;

  glScalef(s.radius(), s.radius(), s.radius());

  glBegin(GL_QUADS);
  float v = 0;
  for(size_t j = 0; j != uDivisions; ++j, v += vDel)
  {
    float u = 0;
    for(size_t i = 0; i != vDivisions; ++i, u += uDel)
    {
      point_type p;
      UnitSquareToSphere::evaluate(u, v, p);

      glNormal3fv(p);
      glVertex3fv(p);

      UnitSquareToSphere::evaluate(u + uDel, v, p);
      glNormal3fv(p);
      glVertex3fv(p);

      UnitSquareToSphere::evaluate(u + uDel, v + vDel, p);
      glNormal3fv(p);
      glVertex3fv(p);

      UnitSquareToSphere::evaluate(u, v + vDel, p);
      glNormal3fv(p);
      glVertex3fv(p);
    } // end for
  } // end for j
  glEnd();

  glPopMatrix();
  glPopAttrib();
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

