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

  image_.fill(black);

  const point eye(0,0,3);
  const point center(0,0,-1);
  const vector up(0,1,0);
  const vector look = normalize(center - eye);

  const vector right = cross(look,up);

  float fovy = 60;
  float fovy_radians = fovy * (3.1428 / 180.0);

  const perspective_sensor perspective(fovy_radians, 1.f);

  std::mt19937_64 rng;

  float v_spacing = 1.f / image_.height();
  float v = v_spacing / 2;
  for(image::size_type row = 0; row < image_.height(); ++row, v += v_spacing)
  {
    float u_spacing = 1.f / image_.width();
    float u = u_spacing / 2;
    for(image::size_type col = 0; col < image_.width(); ++col, u += u_spacing)
    {
      color result = black;

      size_t paths_per_pixel = 20;
      float sample_weight = 1.f / paths_per_pixel;

      for(int path = 0; path < paths_per_pixel; ++path)
      {
        color radiance = black;
        color throughput = white;

        point origin = eye;
        vector direction = sample_with_basis(perspective, right, up, look, u, v);

        // the first bounce is considered to be sampled from a delta distribution
        bool is_delta_sample = true;
        for(int bounce = 2; bounce < max_path_length_; ++bounce)
        {
          ray r(origin, direction);

          auto intersection = scene_.intersect(r);

          if(intersection)
          {
            vector wo = -r.direction();
  
            const surface_primitive& surface = intersection->surface();

            // begin with emission from the hit point
            const differential_geometry &dg = intersection->differential_geometry();

            // sum exitant radiance at the intersection point only on bounces from delta distributions
            if(is_delta_sample)
            {
              scattering_distribution_function e = surface.material().evaluate_emission(dg);
              radiance += throughput * e(wo);
            }

            const point& x = r(intersection->ray_parameter());

            // transform wo into dg's local coordinate system
            wo = dg.localize(wo);
  
            scattering_distribution_function f = surface.material().evaluate_scattering(dg);

            // sum the contribution of each emitter
            for(const auto& emitter : scene_.emitters())
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
                radiance += throughput * f(wo,wi) * dg.abs_cos_theta(wi) * g * e(we) / emitter.pdf(emitter_dg);
              } // end if not shadowed
            } // end for emitter

            // sample next direction
            auto sample = f.sample_direction(rng(), rng(), wo);

            // update throughput
            throughput *= sample.throughput();
            if(!sample.is_delta_sample())
            {
              throughput *= dg.abs_cos_theta(sample.wi());
              throughput /= sample.probability_density();
            }

            // update ray
            origin = dg.point();
            direction = dg.globalize(sample.wi());
            is_delta_sample = sample.is_delta_sample();
          } // end if intersection
          else
          {
            break;
          }
        } // end for bounce

        result += sample_weight * radiance;
      } // end for paths

      image_.raster(col, row) = result;

      progress++;
    } // end for col
  } // end for row
}


} // end igloo


