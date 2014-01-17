#pragma once

#include <commonviewer/CommonViewer.h>
#include <glutviewer/GlutViewer.h>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/matrix.hpp>
#include <igloo/primitives/surface_primitive.hpp>
#include <igloo/surfaces/sphere.hpp>
#include <igloo/surfaces/mesh.hpp>

namespace igloo
{


class test_viewer : public CommonViewer<GlutViewer,KeyEvent,std::string,float3>
{
  public:
    test_viewer(const std::vector<surface_primitive> &primitives, const float4x4 &modelview);

    virtual void draw();

  private:
    const std::vector<surface_primitive> &m_surfaces;

    float4x4 m_modelview;
};


} // end igloo

