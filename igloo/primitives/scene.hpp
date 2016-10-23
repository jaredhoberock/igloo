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

    class surfaces_view
    {
      public:
        surfaces_view(const_iterator begin, const_iterator end)
          : begin_(begin),
            end_(end)
        {}

        using iterator = scene::const_iterator;

        iterator begin() const
        {
          return begin_;
        }

        iterator end() const
        {
          return end_;
        }

      private:
        const_iterator begin_;
        const_iterator end_;
    };

    surfaces_view surfaces() const
    {
      return surfaces_view(begin(), end());
    }

    class emitters_view
    {
      private:
        struct is_emitter
        {
          bool operator()(const surface_primitive& surface) const
          {
            return surface.get_material().is_emitter();
          }
        };

      public:
        emitters_view(const scene& self)
          : self_(self)
        {}

        using iterator = filter_iterator<is_emitter, surfaces_view::iterator>;

        iterator begin() const
        {
          return iterator(is_emitter(), self_.surfaces().begin(), self_.surfaces().end());
        }

        iterator end() const
        {
          return iterator(is_emitter(), self_.surfaces().end(), self_.surfaces().end());
        }

      private:
        const scene& self_;
    };

    emitters_view emitters() const
    {
      return emitters_view(*this);
    }
};


} // end igloo

