#include <igloo/renderers/debug_renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>
#include <igloo/scattering/perspective_sensor.hpp>

namespace igloo
{


debug_renderer::debug_renderer(const scene &s, image &im)
  : m_scene(s), m_image(im)
{}


void debug_renderer::render(const float4x4 &modelview, render_progress &progress)
{
  progress.reset(m_image.width() * m_image.height());

  m_image.fill(black);

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
        const differential_geometry &dg = intersection->differential_geometry();

        vector wo = -normalize(r.direction());

        // transform wo into dg's local coordinate system
        wo = dg.localize(wo);

        vector wi = wo;

        const surface_primitive& surface = intersection->surface();

        scattering_distribution_function f = surface.material().evaluate_scattering(dg);
        scattering_distribution_function e = surface.material().evaluate_emission(dg);

        // XXX we should rotate wo into the basis of the shading point, and then evaluate these functions
        //     to do that, we need a tangent and normal vector
        
        m_image.raster(col, row) = f(wo,wi) * dg.abs_cos_theta(wi) + e(wo);
      } // end if

      progress++;
    } // end for col
  } // end for row
} // end debug_renderer::render()


} // end igloo

