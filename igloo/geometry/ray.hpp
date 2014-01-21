#pragma once

#include <igloo/utility/math_vector.hpp>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/point.hpp>
#include <limits>
#include <iostream>

namespace igloo
{


class ray
{
  public:
    inline ray(const point &origin, const vector &direction)
      : m_origin(origin),
        m_direction(direction),
        m_interval(epsilon(), infinity())
    {}

    inline ray(const point &origin, const point &end)
      : m_origin(origin),
        m_direction(end - origin),
        m_interval(epsilon(), 1)
    {}

    inline ray(const point &origin, const vector &direction, float max_t)
      : m_origin(origin),
        m_direction(direction),
        m_interval(epsilon(), max_t)
    {}

    inline const point &origin() const
    {
      return m_origin;
    }

    inline const vector &direction() const
    {
      return m_direction;
    }

    inline const float2 &interval() const
    {
      return m_interval;
    }

    inline point operator()(float t) const
    {
      return origin() + t * direction();
    }

    inline void end(float t)
    {
      m_interval.y = t;
    }

  private:
    inline static float epsilon()
    {
      return 0.00001;
    }

    inline static float infinity()
    {
      return std::numeric_limits<float>::infinity();
    }

    point m_origin;
    vector m_direction;
    float2 m_interval;
}; // end ray


inline std::ostream &operator<<(std::ostream &os, const ray &r)
{
  return os << r.origin() << " " << r.direction();
} // end operator<<()


} // end igloo

