#include <igloo/igloo.hpp>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/matrix.hpp>

using namespace igloo;

// see gluLookAt man page: we construct the
// transpose of their matrix and inverse of their
// translation
void look_at(igloo::igloo &renderer, float3 eye, float3 center, float3 up)
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
  igloo::igloo renderer;

  std::vector<float> unit_square_points = {-0.5, 0,  0.5,
                                            0.5, 0,  0.5,
                                            0.5, 0, -0.5,
                                           -0.5, 0, -0.5};

  std::vector<unsigned int> unit_square_tris = { 0, 1,  3,
                                                 1, 2,  3};

  // back wall
  renderer.push_matrix();
  renderer.translate(0, 0, -1);
  renderer.rotate(90, 1, 0, 0);
  renderer.scale(2, 2, 2);
  renderer.mesh(unit_square_points.data(), unit_square_points.size() / 3,
                unit_square_tris.data(), unit_square_tris.size() / 3);
  renderer.pop_matrix();

  // floor
  renderer.push_matrix();
  renderer.translate(0,-1,0);
  renderer.scale(2, 2, 2);
  renderer.mesh(unit_square_points.data(), unit_square_points.size() / 3,
                unit_square_tris.data(), unit_square_tris.size() / 3);
  renderer.pop_matrix();

  // ceiling
  renderer.push_matrix();
  renderer.translate(0,1,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(180, 1.0, 0, 0);
  renderer.mesh(unit_square_points.data(), unit_square_points.size() / 3,
                unit_square_tris.data(), unit_square_tris.size() / 3);
  renderer.pop_matrix();

  // left wall
  renderer.push_matrix();
  renderer.translate(-1,0,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(-90, 0, 0, 1);
  renderer.mesh(unit_square_points.data(), unit_square_points.size() / 3,
                unit_square_tris.data(), unit_square_tris.size() / 3);
  renderer.pop_matrix();

  // right wall
  renderer.push_matrix();
  renderer.translate(1,0,0);
  renderer.scale(2, 2, 2);
  renderer.rotate(90, 0, 0, 1);
  renderer.mesh(unit_square_points.data(), unit_square_points.size() / 3,
                unit_square_tris.data(), unit_square_tris.size() / 3);
  renderer.pop_matrix();

  // mirror ball
  renderer.sphere(-0.4, -0.66, -0.15, 0.33);

  // glass ball
  renderer.sphere(0.4, -0.66, 0.25, 0.33);

  look_at(renderer, float3(0,0,3), float3(0,0,-1), float3(0,1,0));

  renderer.render();

  return 0;
}

