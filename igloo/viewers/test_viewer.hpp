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
    test_viewer(const image &im, const scene &s, const float4x4 &modelview);

    virtual void draw();

    virtual void keyPressEvent(KeyEvent *e);

  private:
    void draw_image() const;

    const image &m_image;
    bool m_draw_preview;
};


} // end igloo

