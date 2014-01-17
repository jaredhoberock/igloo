#include <igloo/viewers/test_viewer.hpp>

namespace igloo
{


test_viewer::test_viewer(image &im,
                         const std::vector<surface_primitive> &primitives,
                         const float4x4 &modelview)
  : super_t(primitives, modelview),
    m_image(im)
{
  resize(m_image.width(), m_image.height());
}


void test_viewer::draw()
{
  super_t::draw();
} // end draw()


} // end igloo

