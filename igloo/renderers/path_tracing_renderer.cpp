#include <igloo/renderers/path_tracing_renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>
#include <igloo/scattering/perspective_sensor.hpp>
#include <iostream>
#include <array>
#include <random>

namespace igloo
{


path_tracing_renderer::path_tracing_renderer(const scene &s, image &im, std::size_t max_path_length)
  : scene_(s), image_(im), max_path_length_(max_path_length)
{
  if(max_path_length_ < 2)
  {
    std::clog << "path_tracing_renderer: Setting max_path_length to 3." << std::endl;
    max_path_length_ = 3;
  }
}


void path_tracing_renderer::render(const float4x4 &modelview, render_progress &progress)
{
  progress.reset(image_.width() * image_.height());

  image_.fill(color::black());

  point eye(0,0,3);
  point center(0,0,-1);
  vector up(0,1,0);
  vector look = normalize(center - eye);

  vector right = cross(look,up);

  float fovy = 60;
  float fovy_radians = fovy * (3.1428 / 180.0);

  perspective_sensor perspective(fovy_radians, 1.f);

  std::mt19937_64 rng;

  float v_spacing = 1.f / image_.height();
  float v = v_spacing / 2;
  for(image::size_type row = 0; row < image_.height(); ++row, v += v_spacing)
  {
    float u_spacing = 1.f / image_.width();
    float u = u_spacing / 2;
    for(image::size_type col = 0; col < image_.width(); ++col, u += u_spacing)
    {
      color result = color::black();

      ray r(eye, sample_with_basis(perspective, right, up, look, u, v));

      auto intersection = scene_.intersect(r);
      if(intersection)
      {
        vector wo = -normalize(r.direction());
  
        const surface_primitive& surface = intersection->surface();

        // begin with emission from the hit point
        const differential_geometry &dg = intersection->differential_geometry();
        scattering_distribution_function e = surface.material().evaluate_emission(dg);
        result = e(wo);

        const point& x = r(intersection->ray_parameter());

        // transform wo into dg's local coordinate system
        wo = dg.localize(wo);
  
        scattering_distribution_function f = surface.material().evaluate_scattering(dg);

        // sum the contribution of each emitter
        for(const auto& emitter : scene_.emitters())
        {
          int num_sample_points = 128;
          float sample_weight = 1.f / num_sample_points;

          for(int i = 0; i < num_sample_points; ++i)
          {
            auto emitter_dg = emitter.sample_surface(rng(), rng());

            // construct a ray between x and the point on the emitter
            ray to_emitter(x, emitter_dg.point());

            if(!scene_.is_intersected(to_emitter))
            {
              // evaluate the emitter's material
              scattering_distribution_function e = emitter.material().evaluate_emission(emitter_dg);

              // get the direction to the emitter
              vector wi = normalize(to_emitter.direction());

              // get the direction from the emitter
              vector we = -wi;

              // localize wi to dg's coordinate system
              wi = dg.localize(wi);

              // localize we to emitter_dg's coordinate system
              we = emitter_dg.localize(we);

              // compute geometric term
              float g = emitter_dg.abs_cos_theta(we) / (distance_squared(dg, emitter_dg));

              // accumulate sample
              result += sample_weight * f(wo,wi) * dg.abs_cos_theta(wi) * g * e(we) / emitter.pdf(emitter_dg);
            }
          }
        }
      } // end if

      image_.raster(col, row) = result;

      progress++;
    } // end for col
  } // end for row
}


} // end igloo


