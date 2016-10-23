#pragma once

#include <igloo/renderers/renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/records/image.hpp>

namespace igloo
{


class direct_lighting_renderer : public renderer
{
  public:
    direct_lighting_renderer(const scene &s, image &im);

    void render(const float4x4 &modelview, render_progress &progress);

  private:
    const scene &m_scene;
    image &m_image;
}; // end direct_lighting_renderer


} // end igloo

