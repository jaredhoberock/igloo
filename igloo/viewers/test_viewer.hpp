#pragma once

#include <commonviewer/CommonViewer.h>
#include <glutviewer/GlutViewer.h>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/matrix.hpp>
#include <igloo/surfaces/sphere.hpp>

namespace igloo
{


class test_viewer : public CommonViewer<GlutViewer,KeyEvent,std::string,float3>
{
  public:
    test_viewer(const sphere &s, const float4x4 &modelview);

    virtual void draw();

  private:
    const sphere &m_sphere;

    float4x4 m_modelview;
};


} // end igloo

