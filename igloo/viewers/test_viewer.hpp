#pragma once

#include <igloo/viewers/scene_viewer.hpp>
#include <igloo/records/image.hpp>

namespace igloo
{


class test_viewer : public scene_viewer
{
  private:
    typedef scene_viewer super_t;

  public:
    test_viewer(image &im, const std::vector<surface_primitive> &primitives, const float4x4 &modelview);

    virtual void draw();

  private:
    image &m_image;
};


} // end igloo

