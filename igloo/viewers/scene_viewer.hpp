#pragma once

#include <commonviewer/CommonViewer.h>
#include <glutviewer/GlutViewer.h>
#include <igloo/utility/math_vector.hpp>
#include <igloo/utility/matrix.hpp>
#include <igloo/primitives/surface_primitive.hpp>

namespace igloo
{


// XXX use igloo::vector?
class scene_viewer : public CommonViewer<GlutViewer,KeyEvent,std::string,float3>
{
  public:
    scene_viewer(const std::vector<surface_primitive> &primitives, const float4x4 &modelview);

    virtual void draw();

  private:
    const std::vector<surface_primitive> &m_surfaces;

    float4x4 m_modelview;
};


} // end igloo

