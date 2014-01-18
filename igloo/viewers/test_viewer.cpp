#include <igloo/viewers/test_viewer.hpp>
#include <dependencies/gl++/texture/Texture.h>

namespace igloo
{


test_viewer::test_viewer(const progress_snapshot &progress,
                         const scene &s,
                         const float4x4 &modelview)
  : super_t(s, modelview),
    m_progress(progress),
    m_draw_preview(true)
{
  resize(progress.width(), progress.height());
}


void test_viewer::draw_image() const
{
  glpp::Texture tex;
  tex.create();
  tex.texImage2D(GL_RGB,
                 m_progress.snapshot().width(), m_progress.snapshot().height(), 0,
                 GL_RGB, GL_FLOAT,
                 m_progress.snapshot().data());

  drawTexture(tex);
} // end test_viewer::draw_image()


void test_viewer::draw()
{
  if(m_draw_preview)
  {
    super_t::draw();
  } // end if
  else
  {
    draw_image();
  } // end else
} // end draw()


void test_viewer::keyPressEvent(KeyEvent *e)
{
  switch(e->key())
  {
    case 'P':
    {
      m_draw_preview = !m_draw_preview;
      updateGL();
      break;
    } // end case P

    default:
    {
      super_t::keyPressEvent(e);
      break;
    } // end default
  } // end switch()
} // end test_viewer::keyPressEvent()


} // end igloo

