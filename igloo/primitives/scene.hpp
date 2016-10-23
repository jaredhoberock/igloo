#pragma once

#include <vector>
#include <igloo/primitives/surface_primitive.hpp>
#include <igloo/utility/filter_iterator.hpp>

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

  private:
    struct is_emitter
    {
      bool operator()(const surface_primitive& surface) const
      {
        return surface.get_material().is_emitter();
      }
    };

  public:
    using surface_iterator = std::vector<surface_primitive>::const_iterator;

    surface_iterator surfaces_begin() const
    {
      return begin();
    }

    surface_iterator surfaces_end() const
    {
      return end();
    }

    using emitter_iterator = filter_iterator<is_emitter, surface_iterator>;

    emitter_iterator emitters_begin() const
    {
      return emitter_iterator(is_emitter(), surfaces_begin(), surfaces_end());
    }

    emitter_iterator emitters_end() const
    {
      return emitter_iterator(is_emitter(), surfaces_end(), surfaces_end());
    }

    class emitters_view
    {
      public:
        emitters_view(const scene& self)
          : self_(self)
        {}

        emitter_iterator begin() const
        {
          return self_.emitters_begin();
        }

        emitter_iterator end() const
        {
          return self_.emitters_end();
        }

      private:
        const scene& self_;
    };

    emitters_view all_emitters() const
    {
      return emitters_view(*this);
    }
};


} // end igloo

