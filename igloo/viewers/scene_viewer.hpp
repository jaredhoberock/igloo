#pragma once

#include <commonviewer/CommonViewer.h>
#include <glutviewer/GlutViewer.h>
#include <igloo/utility/math_vector.hpp>
#include <igloo/utility/matrix.hpp>
#include <igloo/primitives/scene.hpp>

namespace igloo
{


// XXX use igloo::vector?
class scene_viewer : public CommonViewer<GlutViewer,KeyEvent,std::string,float3>
{
  public:
    scene_viewer(const scene &s, const float4x4 &modelview);

    virtual void draw();

  private:
    const scene &m_scene;

    float4x4 m_modelview;
};


} // end igloo

