#pragma once

#include <cmath>
#include <igloo/geometry/vector.hpp>

namespace igloo
{


class perspective_sensor
{
  public:
    perspective_sensor(float field_of_view_y, float aspect_ratio)
      : m_near_distance(0.5f / std::tan(0.5f * field_of_view_y)),
        m_aspect_ratio(aspect_ratio)
    {}

    inline vector sample(const vector &tangent,
                         const vector &binormal,
                         const vector &normal,
                         float u0,
                         float u1) const
    {
      return normalize(m_near_distance * binormal + (u0 - 0.5f) * m_aspect_ratio * tangent + (u1 - 0.5f) * normal);
    } // end sample()
 
  private:
    float m_near_distance;
    float m_aspect_ratio;
}; // end perspective_sensor


} // end igloo

