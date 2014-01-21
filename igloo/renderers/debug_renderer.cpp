#include <igloo/renderers/debug_renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>
#include <igloo/shading/perspective_sensor.hpp>

namespace igloo
{


debug_renderer::debug_renderer(const scene &s, image &im)
  : m_scene(s), m_image(im)
{}


void debug_renderer::render(const float4x4 &modelview, render_progress &progress)
{
  progress.reset(m_image.width() * m_image.height());

  m_image.fill(color::black());

  point eye(0,0,3);
  point center(0,0,-1);
  vector up(0,1,0);
  vector look = normalize(center - eye);

  vector right = cross(look,up);

  float fovy = 60;
  float fovy_radians = fovy * (3.1428 / 180.0);

  perspective_sensor perspective(fovy_radians, 1.f);

  float v_spacing = 1.f / m_image.height();
  float v = v_spacing / 2;
  for(image::size_type row = 0; row < m_image.height(); ++row, v += v_spacing)
  {
    float u_spacing = 1.f / m_image.width();
    float u = u_spacing / 2;
    for(image::size_type col = 0; col < m_image.width(); ++col, u += u_spacing)
    {
      ray r(eye, perspective.sample(right,look,up,u,v));

      for(auto &prim : m_scene)
      {
        const sphere *s = dynamic_cast<const sphere*>(&prim.surf());
        if(s)
        {
          float t;
          normal n;
          if(s->intersect(r, t, n))
          {
            m_image.raster(col, row) = color(std::abs(n.x), std::abs(n.y), std::abs(n.z));
          } // end if
        } // end if

        const mesh *m = dynamic_cast<const mesh*>(&prim.surf());
        if(m)
        {
          float t;
          normal n;
          if(m->intersect(r, t, n))
          {
            m_image.raster(col, row) = color(std::abs(n.x), std::abs(n.y), std::abs(n.z));
          } // end if
        } // end if
      } // end for surf

      progress++;
    } // end for col
  } // end for row
} // end debug_renderer::render()


} // end igloo

