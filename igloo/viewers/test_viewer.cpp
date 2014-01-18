#include <igloo/viewers/test_viewer.hpp>
#include <dependencies/gl++/texture/Texture.h>

namespace igloo
{


test_viewer::test_viewer(const image &im,
                         const scene &s,
                         const float4x4 &modelview)
  : super_t(s, modelview),
    m_image(im),
    m_draw_preview(true)
{
  resize(m_image.width(), m_image.height());
}


void test_viewer::draw_image() const
{
  glpp::Texture tex;
  tex.create();
  tex.texImage2D(GL_RGB, m_image.width(), m_image.height(), 0, GL_RGB, GL_FLOAT, m_image.data());

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
  }
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

