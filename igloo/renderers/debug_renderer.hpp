#pragma once

#include <igloo/primitives/scene.hpp>
#include <igloo/records/image.hpp>
#include <igloo/renderers/render_progress.hpp>
#include <igloo/utility/matrix.hpp>

namespace igloo
{


class debug_renderer
{
  public:
    debug_renderer(const scene &s, image &im);

    void render(const float4x4 &modelview, render_progress &progress);

  private:
    const scene &m_scene;
    image &m_image;
}; // end debug_renderer


} // end igloo

