#include <igloo/renderers/direct_lighting_renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>
#include <igloo/shading/perspective_sensor.hpp>
#include <igloo/shading/scattering_distribution_function.hpp>

namespace igloo
{


direct_lighting_renderer::direct_lighting_renderer(const scene &s, image &im)
  : m_scene(s), m_image(im)
{}


void direct_lighting_renderer::render(const float4x4 &modelview, render_progress &progress)
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
      ray r(eye, sample_with_basis(perspective, right, up, look, u, v));

      auto intersection = m_scene.intersect(r);
      if(intersection)
      {
        vector wo = -normalize(r.direction());
  
        const surface_primitive& surface = intersection->surface();

        // begin with emission from the hit point
        const differential_geometry &dg = intersection->differential_geometry();
        scattering_distribution_function e = surface.get_material().evaluate_emission(dg);
        m_image.raster(col, row) += e(wo);

        const point& x = r(intersection->ray_parameter());

        // transform wo into dg's local coordinate system
        wo = dg.localize(wo);
  
        scattering_distribution_function f = surface.get_material().evaluate_scattering(dg);

        // sum the contribution of each emitter
        for(const auto& emitter : m_scene.all_emitters())
        {
          // XXX need to evaluate emission function

          auto light_p = emitter.point_on_surface({0.5,0.5});

          vector wi = normalize(light_p - x);
          wi = dg.localize(wi);
          
          m_image.raster(col, row) += f(wo,wi) * dg.abs_cos_theta(wi);
        }
      } // end if

      progress++;
    } // end for col
  } // end for row
} // end direct_lighting_renderer::render()


} // end igloo


