#pragma once

#include <igloo/viewers/scene_viewer.hpp>
#include <igloo/records/image.hpp>
#include <igloo/renderers/render_progress.hpp>
#include <dependencies/gl++/texture/Texture.h>
#include <chrono>

namespace igloo
{


class progress_snapshot : public render_progress
{
  private:
    typedef render_progress super_t;

  public:
    inline progress_snapshot(const image &im)
      : super_t(),
        m_image(im),
        m_snapshot(im)
    {
      // set the last update to a time in the past to force an unconditional
      // update to the texture on the next call to on_progress()
      m_last_update = std::chrono::system_clock::now() - std::chrono::hours(24);
    }

    inline std::size_t width() const
    {
      return m_snapshot.width();
    }

    inline std::size_t height() const
    {
      return m_snapshot.height();
    }

    inline const image &snapshot() const
    {
      return m_snapshot;
    }

  protected:
    inline virtual void on_progress(std::size_t, std::size_t)
    {
      // every 30 ms, update_snapshot()
      if(std::chrono::system_clock::now() - m_last_update > std::chrono::milliseconds(30))
      {
        update_snapshot();
      } // end if
    } // end on_progress()

  private:
    inline void update_snapshot()
    {
      m_snapshot = m_image;
      m_last_update = std::chrono::system_clock::now();
    }

    const image &m_image;
    image m_snapshot;
    std::chrono::time_point<std::chrono::system_clock> m_last_update;
};



class test_viewer : public scene_viewer
{
  private:
    typedef scene_viewer super_t;

  public:
    test_viewer(const progress_snapshot &progress, const scene &s, const float4x4 &modelview);

    virtual void draw();

    virtual void keyPressEvent(KeyEvent *e);

  private:
    void draw_image() const;

    const progress_snapshot &m_progress;
    bool m_draw_preview;
};


} // end igloo

