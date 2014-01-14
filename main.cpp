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

  renderer.sphere(-0.4, -0.66, -0.15, 0.33);

  look_at(renderer, float3(0,0,3), float3(0,0,-1), float3(0,1,0));

  renderer.render();

  return 0;
}

