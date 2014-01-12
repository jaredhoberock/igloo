#include <igloo/igloo.hpp>

int main()
{
  igloo::igloo renderer;

  renderer.sphere(-0.4, -0.66, -0.15, 0.33);

  renderer.render();

  return 0;
}

