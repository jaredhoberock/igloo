#pragma once

#include <igloo/geometry/point.hpp>
#include <algorithm>
#include <numeric>
#include <array>
#include <limits>


namespace igloo
{


class bounding_box : public std::array<point,2>
{
  private:
    using super_t = std::array<point,2>;

    static point positive_infinity()
    {
      float inf = std::numeric_limits<float>::infinity();

      return point(inf,inf,inf);
    }

    static point negative_infinity()
    {
      float inf = std::numeric_limits<float>::infinity();

      return point(-inf,-inf,-inf);
    }

  public:
    using super_t::super_t;

    bounding_box(const bounding_box&) = default;

    /// Constructs a new bounding_box
    bounding_box(const point& min_corner, const point& max_corner)
      : super_t{min_corner, max_corner}
    {}

    /// Constructs an empty bounding_box.
    bounding_box()
      : bounding_box(positive_infinity(), negative_infinity())
    {}

    /// Constructs a bounding_box bounding all of the given points.
    template<class Range>
    bounding_box(const Range& points)
      : bounding_box(std::accumulate(points.begin(), points.end(), bounding_box()))
    {}

    const point& min() const
    {
      return (*this)[0];
    }

    point& min()
    {
      return (*this)[0];
    }

    const point& max() const
    {
      return (*this)[1];
    }

    point& max()
    {
      return (*this)[1];
    }

    /// Expands this bounding_box to bound the given point.
    void expand_to_bound(const point& x)
    {
      for(int i = 0; i < 3; ++i)
      {
        min()[i] = std::min(min()[i], x[i]);

        // max()[i] is treated as non-inclusive, so return the next floating point value after x[i]
        // to be sure we include x[i]
        max()[i] = std::max(max()[i], std::nextafter(x[i], std::numeric_limits<float>::infinity()));
      }
    }

    /// Expands this bounding_box to bound the given point.
    bounding_box& operator+=(const point& x)
    {
      expand_to_bound(x);
      return *this;
    }

    /// Returns a bounding_box bounding all the points bounded by this one as well as x.
    bounding_box operator+(const point& x) const
    {
      bounding_box result = *this;
      result += x;
      return result;
    }

    /// Returns true if the given point is bounded by this bounding_box.
    bool bounds(const point& x) const
    {
      for(int i = 0; i < 3; ++i)
      {
        if(x[i] <  min()[i]) return false;
        if(x[i] >= max()[i]) return false;
      }

      return true;
    }
};


} // end igloo

