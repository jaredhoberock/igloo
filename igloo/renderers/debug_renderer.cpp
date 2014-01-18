#include <igloo/renderers/debug_renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/surfaces/sphere.hpp>

namespace igloo
{


debug_renderer::debug_renderer(const scene &s, image &im)
  : m_scene(s), m_image(im)
{}


void debug_renderer::render(const float4x4 &modelview, render_progress &progress)
{
  progress.reset(m_image.width() * m_image.height());

  m_image.fill(spectrum::black());

  point eye(0,0,3);
  point center(0,0,-1);
  vector up(0,1,0);
  vector look = normalize(center - eye);

  vector right = cross(look,up);

  float fovy = 60;
  float fovy_radians = fovy * (3.1428 / 180.0);

  // compute the location of the ll corner of the viewport, in world coordinates
  auto near = 1.0f / std::tan(0.5f * fovy_radians);

  float aspect_ratio = float(m_image.width()) / m_image.height();

  point ll = eye + near*look - aspect_ratio*right - up;

  for(image::size_type row = 0; row < m_image.height(); ++row)
  {
    for(image::size_type col = 0; col < m_image.width(); ++col)
    {
      float u = float(col) / m_image.width();
      float v = float(row) / m_image.height();

      auto shoot_me = ll + (2.0f * aspect_ratio * u * right) + (2.0f * v * up);

      // create a ray from the eye to the point on the viewport
      ray r(eye, shoot_me - eye);

      for(auto &prim : m_scene)
      {
        const sphere *s = dynamic_cast<const sphere*>(&prim.surf());
        if(s)
        {
          float t;
          normal n;
          if(s->intersect(r, t, n))
          {
            m_image.raster(col, row) = spectrum(std::abs(n.x), std::abs(n.y), std::abs(n.z));
          } // end if
        } // end if
      } // end for surf

      progress++;
    } // end for col
  } // end for row
} // end debug_renderer::render()


} // end igloo

