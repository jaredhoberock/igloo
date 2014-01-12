#pragma once

#include <commonviewer/CommonViewer.h>
#include <glutviewer/GlutViewer.h>
#include <gpcpu/Vector.h>
#include <igloo/surfaces/sphere.hpp>

namespace igloo
{


class test_viewer : public CommonViewer<GlutViewer,KeyEvent,std::string,gpcpu::float3>
{
  public:
    test_viewer(const sphere &s);

    virtual void draw();

  private:
    const sphere &m_sphere;
};


} // end igloo

