#pragma once

#include <igloo/renderers/renderer.hpp>
#include <igloo/primitives/scene.hpp>
#include <igloo/records/image.hpp>

namespace igloo
{


class path_tracing_renderer : public renderer
{
  public:
    path_tracing_renderer(const scene &s, image &im);

    void render(const float4x4 &modelview, render_progress &progress);

  private:
    const scene &m_scene;
    image &m_image;
};


}

