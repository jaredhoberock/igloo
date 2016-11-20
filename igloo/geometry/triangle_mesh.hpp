#pragma once

#include <vector>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <type_traits>
#include <dependencies/bounding_box_hierarchy/bounding_box_hierarchy.hpp>
#include <igloo/utility/requires.hpp>
#include <igloo/utility/optional.hpp>
#include <igloo/geometry/bounding_box.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>
#include <igloo/geometry/ray.hpp>

namespace igloo
{


class triangle_mesh
{
  private:

  public:
    using triangle = uint3;
    using barycentric = float2;

  private:
    using point_container = std::vector<point>;
    using parametric_container = std::vector<parametric>;
    using normal_container = std::vector<normal>;
    using triangle_container = std::vector<triangle>;

  public:
    using point_iterator = point_container::const_iterator;
    using parametric_iterator = parametric_container::const_iterator;
    using normal_iterator = normal_container::const_iterator;
    using triangle_iterator = triangle_container::const_iterator;

  private:
    struct construct_privately_t {};

    template<class Range1,
             class Range2,
             class Range3,
             class Range4>
    inline triangle_mesh(construct_privately_t,
                         Range1&& points,
                         Range2&& parametrics,
                         Range3&& normals,
                         Range4&& triangles)
      : m_points(std::forward<Range1>(points)),
        m_parametrics(std::forward<Range2>(parametrics)),
        m_normals(std::forward<Range3>(normals)),
        m_triangles(std::forward<Range4>(triangles)),
        m_bbh(m_triangles, [this](const triangle& tri)
        {
          return bounding_box(tri);
        })
    {}

  public:
    template<class Range1, class Range2,
             IGLOO_REQUIRES(
               std::is_constructible<point_container, Range1&&>::value and
               std::is_constructible<triangle_container, Range2&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& triangles)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::vector<parametric>(),
                      std::vector<normal>(),
                      std::forward<Range2>(triangles))
    {}


    template<class Range1, class Range2, class Range3,
             IGLOO_REQUIRES(
               std::is_constructible<point_container, Range1&&>::value and
               std::is_constructible<parametric_container, Range2&&>::value and
               std::is_constructible<triangle_container, Range3&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& parametrics,
                         Range3&& triangles)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::forward<Range2>(parametrics),
                      std::vector<normal>(),
                      std::forward<Range3>(triangles))
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      }
    }


    template<class Range1, class Range2, class Range3,
             IGLOO_REQUIRES(
               std::is_constructible<point_container, Range1&&>::value and
               std::is_constructible<normal_container, Range2&&>::value and
               std::is_constructible<triangle_container, Range3&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& normals,
                         Range3&& triangles)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::vector<parametric>(),
                      std::forward<Range2>(normals),
                      std::forward<Range3>(triangles))
    {
      if(m_normals.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != points.size()");
      }
    }


    template<class Range1, class Range2, class Range3,
             IGLOO_REQUIRES(
                std::is_constructible<point_container, Range1&&>::value and
                std::is_constructible<triangle_container, Range2&&>::value and
                std::is_constructible<normal_container, Range3&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& triangles,
                         Range3&& normals)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::vector<parametric>(),
                      std::forward<Range3>(normals),
                      std::forward<Range2>(triangles))
    {
      if(m_normals.size() != m_triangles.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != triangles.size()");
      }
    }


    template<class Range1, class Range2, class Range3, class Range4,
             IGLOO_REQUIRES(
               std::is_constructible<point_container, Range1&&>::value and
               std::is_constructible<parametric_container, Range2&&>::value and
               std::is_constructible<normal_container, Range3&&>::value and
               std::is_constructible<triangle_container, Range4&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& parametrics,
                         Range3&& normals,
                         Range4&& triangles)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::forward<Range2>(parametrics),
                      std::forward<Range3>(normals),
                      std::forward<Range4>(triangles))
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      }

      if(m_normals.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != points.size()");
      }
    }


    template<class Range1, class Range2, class Range3, class Range4,
             IGLOO_REQUIRES(
               std::is_constructible<point_container, Range1&&>::value and
               std::is_constructible<parametric_container, Range2&&>::value and
               std::is_constructible<triangle_container, Range3&&>::value and
               std::is_constructible<normal_container, Range4&&>::value
             )>
    inline triangle_mesh(Range1&& points,
                         Range2&& parametrics,
                         Range3&& triangles,
                         Range4&& normals)
      : triangle_mesh(construct_privately_t{},
                      std::forward<Range1>(points),
                      std::forward<Range2>(parametrics),
                      std::forward<Range4>(normals),
                      std::forward<Range3>(triangles))
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      }

      if(m_normals.size() != m_triangles.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != triangles.size()");
      }
    }


    /*! \return normals_size() == vertices_size()
     */
    inline bool has_vertex_normals() const
    {
      return normals_size() == vertices_size();
    } // end has_vertex_normals()


    /*! \return The number of vertices.
     */
    inline std::size_t vertices_size() const
    {
      return m_points.size();
    } // end vertices_size()


    /*! \return Whether or not this triangle_mesh has per-vertex parametric coordinates.
     */
    inline bool has_parametrics() const
    {
      return !m_parametrics.empty();
    } // end has_parametrics();


    /*! \return Whether or not this triangle_mesh has normal vectors.
     */
    inline bool has_normals() const
    {
      return !m_normals.empty();
    } // end has_normals()


    /*! \return The number of normals.
     *  \note This is either 0, or equal to vertices_size() or triangles().size().
     */
    inline std::size_t normals_size() const
    {
      return m_normals.size();
    } // end normals_size()


    /*! \return An iterator pointing to the beginning of the collection of points.
     */
    inline point_iterator points_begin() const
    {
      return m_points.begin();
    }

    /*! \return An iterator pointing to the end of the collection of points.
     */
    inline point_iterator points_end() const
    {
      return m_points.end();
    }

    /*! \return A pointer pointing to the array of points.
     */
    inline const point *points_data() const
    {
      return m_points.data();
    }

    /*! \return A iterator pointing to the beginning of the collection of parametrics.
     */
    inline parametric_iterator parametrics_begin() const
    {
      return m_parametrics.begin();
    }

    /*! \return A iterator pointing to the end of the collection of parametrics.
     */
    inline parametric_iterator parametrics_end() const
    {
      return m_parametrics.end();
    }

    /*! \return A pointer pointing to the array of parametrics.
     */
    inline const parametric *parametrics_data() const
    {
      return m_parametrics.data();
    }

    /*! \return A iterator pointing to the beginning of the collection of normals.
     */
    inline normal_iterator normals_begin() const
    {
      return m_normals.begin();
    }

    /*! \return A iterator pointing to the end of the collection of normals.
     */
    inline normal_iterator normals_end() const
    {
      return m_normals.end();
    }

    /*! \return A pointer pointing to the array of normals.
     */
    inline const normal *normals_data() const
    {
      return m_normals.data();
    }

  private:
    struct triangles_view
    {
      triangle_iterator begin() const
      {
        return begin_;
      }

      triangle_iterator end() const
      {
        return end_;
      }

      size_t size() const
      {
        return end() - begin();
      }

      triangle_iterator begin_, end_;
    };

  public:
    /*! \return A view of the collection of triangles
     */
    inline triangles_view triangles() const
    {
      return triangles_view{m_triangles.begin(), m_triangles.end()};
    }

    /*! \return A pointer pointing to the array of triangles.
     */
    inline const triangle *triangles_data() const
    {
      return m_triangles.data();
    }

    /*! \param tri The triangle of interest.
     *  \return The surface area of tri.
     */
    inline float surface_area(const triangle &tri) const
    {
      float3 e0 = m_points[tri[1]] - m_points[tri[0]];
      float3 e1 = m_points[tri[2]] - m_points[tri[0]];
      return 0.5f * norm(cross(e0,e1));
    } // end surface_area()

    /*! \return The surface area of this mesh
     */
    inline float surface_area() const
    {
      return std::accumulate(triangles().begin(), triangles().end(), 0.f, [this](float partial_area, const triangle& tri)
      {
        return partial_area + surface_area(tri);
      });
    } // end surface_area();

    /// Returns a bounding_box bounding the given triangle.
    /// \param tri The triangle of interest.
    /// \return A bounding_box bounding all the points of tri.
    igloo::bounding_box bounding_box(const triangle& tri) const
    {
      igloo::bounding_box result;
      result += m_points[tri[0]];
      result += m_points[tri[1]];
      result += m_points[tri[2]];
      return result;
    }

    /*! Tests a ray and a triangle for intersection.
     *  \param r The ray of interest.
     *  \param tri The triangle of interest.
     *  \return false, if no intersection exists;
     *          otherwise the ray parameter, and barycentric coordinates at the intersection.
     */
    inline optional<std::pair<float,barycentric>>
      intersect(const ray &r, const triangle &tri) const
    {
      const point &p0 = m_points[tri.x];
      const point &p1 = m_points[tri.y];
      const point &p2 = m_points[tri.z];

      vector e1 = p1 - p0;
      vector e2 = p2 - p0;
      vector s1 = r.direction().cross(e2);
      float divisor = dot(s1,e1);
      if(divisor == 0.0f)
      {
        return nullopt;
      } // end if

      float inv_divisor = 1.0f / divisor;

      // compute barycentric coordinates 
      vector d = r.origin() - p0;
      float b0 = dot(d,s1) * inv_divisor;
      if(b0 < 0.0f || b0 > 1.0f)
      {
        return nullopt;
      } // end if

      vector s2 = cross(d,e1);
      float b1 = dot(r.direction(), s2) * inv_divisor;
      if(b1 < 0.0f || b0 + b1 > 1.0f)
      {
        return nullopt;
      } // end if

      // compute t
      float t = inv_divisor * dot(e2,s2);

      // t must lie within valid interval
      if(!r.within_interval(t))
      {
        return nullopt;
      } // end if

      return std::make_pair(t, barycentric(b0,b1));
    } // end intersect()

    /*! Tests a ray and this triangle_mesh for intersection.
     *  \param r The ray of interest.
     *  \return false, if no intersection exists;
     *          otherwise returns the triangle, ray parameter, and barycentric coordinates at the intersection.
     */
    inline optional<std::tuple<triangle_iterator,float,barycentric>>
      intersect(const ray &r) const
    {
      using intersection = optional<std::tuple<triangle_iterator,float,barycentric>>;

      intersection init = nullopt;

      point origin = r.origin() + r.begin() * r.direction();
      float max_t = r.end();

      auto result = m_bbh.intersect(origin, r.direction(), init,
        [&](const triangle& tri, const point&, const vector&, intersection result)
        {
          auto this_result = intersect(r, tri);
          if(this_result)
          {
            float t;
            barycentric b;
            std::tie(t,b) = *this_result;

            if(!result || t < std::get<float>(*result))
            {
              result = std::make_tuple(to_iterator(tri), t, b);
            }
          }

          return result;
        },
        [=](const intersection& i)
        {
          return i ? std::get<float>(*i) : max_t;
        }
      );

      return result;
    } // end intersect()


    inline point point_at(const triangle& tri, const barycentric &b) const
    {
      return interpolate_point(tri,b);
    } // end point_at()


    inline point point_at(triangle_iterator tri, const barycentric &b) const
    {
      return point_at(*tri,b);
    } // end point_at()


    inline parametric parametric_at(triangle_iterator tri, const barycentric &b) const
    {
      if(!has_parametrics()) return igloo::parametric(0.f);

      return interpolate_parametric(*tri,b);
    } // end parametric_at()


    inline normal normal_at(triangle_iterator tri, const barycentric &b) const
    {
      // XXX might want to create a face normal instead
      if(!has_normals()) return igloo::normal(0.f);

      return has_vertex_normals() ? interpolate_normal(*tri, b) : m_normals[tri - triangles().begin()];
    } // end normal_at()


    inline std::pair<vector,vector> parametric_derivatives(triangle_iterator tri) const
    {
      const point& p1 = m_points[tri->x];
      const point& p2 = m_points[tri->y];
      const point& p3 = m_points[tri->z];

      vector dp1 = p1 - p3;
      vector dp2 = p2 - p3;

      vector dpdu;
      vector dpdv;

      if(has_parametrics())
      {
        const parametric& uv0 = m_parametrics[tri->x];
        const parametric& uv1 = m_parametrics[tri->y];
        const parametric& uv2 = m_parametrics[tri->z];

        // see PBRT v2 p143
        float du1 = uv0[0] - uv2[0];
        float du2 = uv1[0] - uv2[0];
        float dv1 = uv0[1] - uv2[1];
        float dv2 = uv1[1] - uv2[1];

        float determinant = du1 * dv2 - dv1 * du2;

        if(determinant == 0)
        {
          // the determinant doesn't exist, so just create an orthonormal_basis around the normal vector
          std::tie(std::ignore, dpdu, dpdv) = orthonormal_basis(dp1.cross(dp2));
        }
        else
        {
          float inv_determinant = 1.f / determinant;

          dpdu = inv_determinant * ( dv2 * dp1 - dv1 * dp2);
          dpdv = inv_determinant * (-du2 * dp1 + du1 * dp2);
        }
      }
      else
      {
        // no parametrics, so just create an orthonormal basis around the normal vector
        std::tie(std::ignore, dpdu, dpdv) = orthonormal_basis(dp1.cross(dp2));
      }

      return std::make_pair(dpdu, dpdv);
    }


  private:
    triangle_iterator to_iterator(const triangle& tri) const
    {
      return m_triangles.begin() + (&tri - m_triangles.data());
    }

    template<class T>
    static inline T interpolate(const barycentric& b, const T& x0, const T& x1, const T& x2)
    {
      float b0 = 1.f - b.x - b.y;

      return b0 * x0 + b.x * x1 + b.y * x2;
    } // end interpolate()


    inline point interpolate_point(const triangle& tri, const barycentric& b) const
    {
      const point &x0 = m_points[tri.x];
      const point &x1 = m_points[tri.y];
      const point &x2 = m_points[tri.z];

      return interpolate(b, x0, x1, x2);
    } // end interpolate_point()


    inline parametric interpolate_parametric(const triangle &tri, const barycentric &b) const
    {
      const parametric &p0 = m_parametrics[tri.x];
      const parametric &p1 = m_parametrics[tri.y];
      const parametric &p2 = m_parametrics[tri.z];

      return interpolate(b, p0, p1, p2);
    } // end interpolate_parametric()


    inline normal interpolate_normal(const triangle &tri, const barycentric &b) const
    {
      const normal &n0 = m_normals[tri.x];
      const normal &n1 = m_normals[tri.y];
      const normal &n2 = m_normals[tri.z];

      return interpolate(b, n0, n1, n2);
    } // end interpolate_normal()


    point_container                  m_points;
    parametric_container             m_parametrics;
    normal_container                 m_normals;
    triangle_container               m_triangles;
    bounding_box_hierarchy<triangle> m_bbh;
};


} // end igloo

