#pragma once

#include <igloo/utility/matrix.hpp>
#include <igloo/renderers/render_progress.hpp>

namespace igloo
{


class renderer
{
  public:
    virtual void render(const float4x4 &modelview, render_progress &progress) = 0;
}; // end renderer

} // end igloo

