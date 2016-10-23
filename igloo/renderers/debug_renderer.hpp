#pragma once

#include <igloo/renderers/renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/records/image.hpp>

namespace igloo
{


class debug_renderer : public renderer
{
  public:
    debug_renderer(const scene &s, image &im);

    void render(const float4x4 &modelview, render_progress &progress);

  private:
    const scene &m_scene;
    image &m_image;
}; // end debug_renderer


} // end igloo

