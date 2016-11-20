#include <igloo/context.hpp>
#include <igloo/materials/glass.hpp>
#include <igloo/materials/matte.hpp>
#include <igloo/materials/light.hpp>
#include <igloo/utility/math_vector.hpp>
#include <igloo/utility/matrix.hpp>
#include <memory>

using namespace igloo;

// see gluLookAt man page: we construct the
// transpose of their matrix and inverse of their
// translation
void look_at(igloo::context &renderer, float3 eye, float3 center, float3 up)
{
  float3 f = normalize(center - eye);
  up = normalize(up);
  float3 s = cross(f,up);
  float3 u = cross(s,f);

  float4x4 m(s.x, u.x, -f.x, 0,
             s.y, u.y, -f.y, 0,
             s.z, u.z, -f.z, 0,
               0,   0,    0, 1);

  renderer.translate(eye.x, eye.y, eye.z);
  renderer.mult_matrix(m);
} // end look_at()


int main()
{
  igloo::context renderer;

  float unit_square_points[] = {-0.5, 0,  0.5,
                                 0.5, 0,  0.5,
                                 0.5, 0, -0.5,
                                -0.5, 0, -0.5};

  unsigned int unit_square_tris[] = { 0, 1,  3,
                                      1, 2,  3};

  color light_power(20,20,20);

  float light_surface_area = 0.5f * 0.5f; 
  color light_radiosity = light_power / light_surface_area;

  // create some materials
  renderer.material(make_material("igloo::matte", {{"albedo", color(0.8, 0.1, 0.1)}}), "red");
  renderer.material(make_material("igloo::matte", {{"albedo", color(0.1, 0.8, 0.1)}}), "green");
  renderer.material(make_material("igloo::matte", {{"albedo", color(0.8, 0.8, 0.8)}}), "white");
  renderer.material(make_material("igloo::glass", {{"eta", 1.5f}, {"reflectance", color(1.0, 1.0, 1.0)}, {"transmittance", color(1.0, 1.0, 1.0)}}), "glass");
  renderer.material(make_material("igloo::light", {{"radiosity", light_radiosity}}), "light");

  // back wall
  renderer.attribute("material", "white");
  renderer.push_matrix();
  renderer.translate(0, 0, -1);
  renderer.rotate(90, 1, 0, 0);
  renderer.scale(2, 2, 2);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  // floor
  renderer.attribute("material", "white");
  renderer.push_matrix();
  renderer.translate(0,-1,0);
  renderer.scale(2, 2, 2);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  // ceiling
  renderer.attribute("material", "white");
  renderer.push_matrix();
  renderer.translate(0,1,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(180, 1.0, 0, 0);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  // left wall
  renderer.attribute("material", "red");
  renderer.push_matrix();
  renderer.translate(-1,0,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(-90, 0, 0, 1);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  // right wall
  renderer.attribute("material", "green");
  renderer.push_matrix();
  renderer.translate(1,0,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(90, 0, 0, 1);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  // mirror ball
  renderer.attribute("material", "default");
  renderer.sphere(-0.4, -0.66, -0.15, 0.33);

  // glass ball
  renderer.attribute("material", "glass");
  renderer.sphere(0.4, -0.66, 0.25, 0.33);

  // ceiling light
  renderer.attribute("material", "light");
  renderer.push_matrix();
  renderer.translate(0, 0.95, 0);
  renderer.scale(0.5, 0.5, 0.5);
  renderer.rotate(180, 1, 0, 0);
  renderer.mesh(unit_square_points, unit_square_tris);
  renderer.pop_matrix();

  look_at(renderer, float3(0,0,3), float3(0,0,-1), float3(0,1,0));

  // use path tracing renderer
  renderer.attribute("renderer", "path_tracing");

  renderer.render();

  return 0;
}

