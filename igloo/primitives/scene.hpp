#pragma once

#include <vector>
#include <igloo/primitives/surface_primitive.hpp>

namespace igloo
{


class scene : public std::vector<surface_primitive>
{
  public:
    class intersection : public igloo::intersection
    {
      public:
        intersection(const igloo::intersection& inter, const surface_primitive& surface)
          : igloo::intersection(inter),
            surface_(surface)
        {}

        intersection(igloo::intersection&& inter, const surface_primitive& surface)
          : igloo::intersection(std::move(inter)),
            surface_(surface)
        {}

        const surface_primitive& surface() const
        {
          return surface_;
        }

      private:
        const surface_primitive& surface_;
    };

    /*! Tests for intersection between a ray and this scene.
     *  \param r The ray of interest.
     *  \param nullopt if no interest exists, otherwise the details of the intersection.
     */
    optional<intersection> intersect(const ray &r) const;
};


} // end igloo

