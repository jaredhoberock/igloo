#include <igloo/renderers/debug_renderer.hpp>

namespace igloo
{


debug_renderer::debug_renderer(const scene &s, image &im)
  : m_scene(s), m_image(im)
{}


void debug_renderer::render(render_progress &progress)
{
  progress.reset(m_image.width() * m_image.height());

  m_image.fill(spectrum::red());

  std::cout << "debug_renderer::render(): updating progress" << std::endl;
  progress += m_image.width() * m_image.height();
} // end debug_renderer::render()


} // end igloo

