#pragma once

#include <vector>
#include <stdexcept>
#include <utility>
#include <tuple>
#include <igloo/utility/optional.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>
#include <igloo/geometry/ray.hpp>

namespace igloo
{


class triangle_mesh
{
  public:
    typedef uint3  triangle;
    typedef float2 barycentric;

    typedef std::vector<point>::const_iterator      point_iterator;
    typedef std::vector<parametric>::const_iterator parametric_iterator;
    typedef std::vector<normal>::const_iterator     normal_iterator;
    typedef std::vector<triangle>::const_iterator   triangle_iterator;

    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<triangle> &triangles)
      : m_points(points),
        m_triangles(triangles)
    {}


    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<parametric> &parametrics,
                         const std::vector<triangle> &triangles)
      : m_points(points),
        m_parametrics(parametrics),
        m_triangles(triangles)
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      } // end if
    } // end triangle_mesh::triangle_mesh()


    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<normal> &normals,
                         const std::vector<triangle> &triangles)
      : m_points(points),
        m_normals(normals),
        m_triangles(triangles)
    {
      if(m_normals.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != points.size()");
      } // end if
    } // end triangle_mesh::triangle_mesh()


    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<triangle> &triangles,
                         const std::vector<normal> &normals)
      : m_points(points),
        m_normals(normals),
        m_triangles(triangles)
    {
      if(m_normals.size() != m_triangles.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != triangles.size()");
      } // end if
    } // end triangle_mesh::triangle_mesh()


    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<parametric> &parametrics,
                         const std::vector<normal> &normals,
                         const std::vector<triangle> &triangles)
      : m_points(points),
        m_parametrics(parametrics),
        m_normals(normals),
        m_triangles(triangles)
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      } // end if

      if(m_normals.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != points.size()");
      } // end if
    } // end triangle_mesh::triangle_mesh()


    inline triangle_mesh(const std::vector<point> &points,
                         const std::vector<parametric> &parametrics,
                         const std::vector<triangle> &triangles,
                         const std::vector<normal> &normals)
      : m_points(points),
        m_parametrics(parametrics),
        m_normals(normals),
        m_triangles(triangles)
    {
      if(m_parametrics.size() != m_points.size())
      {
        throw std::logic_error("triangle_mesh ctor: parametrics.size() != points.size()");
      } // end if

      if(m_normals.size() != m_triangles.size())
      {
        throw std::logic_error("triangle_mesh ctor: normals.size() != triangles.size()");
      } // end if
    } // end triangle_mesh::triangle_mesh()


    /*! Constructor creates a new triangle_mesh from a list of points and triangles.
     *  \param points_first The first element in the list of points.
     *  \param points_last One past the last element in the list of points.
     *  \param triangles_first The first element in the list of triangles.
     *  \param triangle_last One past the last element in the list of triangles.
     */
    template<typename PointIterator, typename TriangleIterator>
    triangle_mesh(PointIterator points_first, PointIterator points_last,
                  TriangleIterator triangles_first, TriangleIterator triangles_last)
      : m_points(points_first, points_last),
        m_triangles(triangles_first, triangles_last)
    {}


    /*! Constructor creates a new triangle_mesh from a list of points, parametrics, and triangles.
     *  \param points_first The first element in the list of points.
     *  \param points_last One past the last element in the list of points.
     *  \param parametrics_first The first element in the list of parametrics.
     *  \param triangles_first The first element in the list of triangles.
     *  \param triangle_last One past the last element in the list of triangles.
     *  \note The list of parametrics must be the same size as the list of points.
     */
    template<typename PointIterator, typename ParametricIterator, typename TriangleIterator>
    triangle_mesh(PointIterator points_first, PointIterator points_last,
                  ParametricIterator parametrics_first,
                  TriangleIterator triangles_first, TriangleIterator triangles_last)
      : m_points(points_first, points_last),
        m_parametrics(parametrics_first, parametrics_first + (points_last - points_first)),
        m_triangles(triangles_first, triangles_last)
    {}


    /*! Constructor creates a new triangle_mesh from a list of points, parametrics, normals, and triangles.
     *  \param points_first The first element in the list of points.
     *  \param points_last One past the last element in the list of points.
     *  \param parametrics_first The first element in the list of parametrics.
     *  \param normals_first The first element in the list of normals.
     *  \param triangles_first The first element in the list of triangles.
     *  \param triangle_last One past the last element in the list of triangles.
     *  \note The list of parametrics and the list of normals must be the same size as the list of points.
     */
    template<typename PointIterator, typename ParametricIterator, typename NormalIterator, typename TriangleIterator>
    triangle_mesh(PointIterator points_first, PointIterator points_last,
                  ParametricIterator parametrics_first,
                  NormalIterator normals_first,
                  TriangleIterator triangles_first, TriangleIterator triangles_last)
      : m_points(points_first, points_last),
        m_parametrics(parametrics_first, parametrics_first + (points_last - points_first)),
        m_normals(normals_first, normals_first + (points_last - points_first)),
        m_triangles(triangles_first, triangles_last)
    {}


    /*! Constructor creates a new triangle_mesh from a list of points, parametrics, triangles, and normals
     *  \param points_first The first element in the list of points.
     *  \param points_last One past the last element in the list of points.
     *  \param parametrics_first The first element in the list of parametrics.
     *  \param triangles_first The first element in the list of triangles.
     *  \param normals_first The first element in the list of normals.
     *  \param triangle_last One past the last element in the list of triangles.
     *  \note The list of parametrics must be the same size as the list of points.
     *  \note The list of normals must be the same size as the list of triangles.
     */
    template<typename PointIterator, typename ParametricIterator, typename NormalIterator, typename TriangleIterator>
    triangle_mesh(PointIterator points_first, PointIterator points_last,
                  ParametricIterator parametrics_first,
                  TriangleIterator triangles_first, TriangleIterator triangles_last,
                  NormalIterator normals_first)
      : m_points(points_first, points_last),
        m_parametrics(parametrics_first, parametrics_first + (points_last - points_first)),
        m_normals(normals_first, normals_first + (triangles_first - triangles_last)),
        m_triangles(triangles_first, triangles_last)
    {}


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
     *  \note This is either 0, or equal to vertices_size() or triangles_size().
     */
    inline std::size_t normals_size() const
    {
      return m_normals.size();
    } // end normals_size()


    /*! \return The number of triangles.
     */
    inline std::size_t triangles_size() const
    {
      return m_triangles.size();
    } // end triangles_size()


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

    /*! \return A iterator pointing to the beginning of the collection of triangles.
     */
    inline triangle_iterator triangles_begin() const
    {
      return m_triangles.begin();
    }

    /*! \return A iterator pointing to the end of the collection of triangles.
     */
    inline triangle_iterator triangles_end() const
    {
      return m_triangles.end();
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

      return std::make_pair(t, barycentric(b0,b1));
    } // end intersect()

    /*! Tests a ray and this triangle_mesh for intersection.
     *  \param r The ray of interest.
     *  \return false, if no intersection exists;
     *          otherwise returns the triangle, ray parameter, and barycentric coordinates at the intersection.
     */
    inline optional<std::tuple<triangle_iterator,float,barycentric>>
      intersect(const ray &r_) const
    {
      optional<std::tuple<triangle_iterator,float,barycentric>> result;

      ray r = r_;

      // XXX this is really a reduction
      //     it requires something like transform_min_element
      for(auto tri_iter = triangles_begin();
          tri_iter != triangles_end();
          ++tri_iter)
      {
        auto this_result = intersect(r, *tri_iter);
        if(this_result)
        {
          float t;
          barycentric b;
          std::tie(t,b) = *this_result;

          // shorten ray
          r.end(std::get<0>(*this_result));
          result = std::make_tuple(tri_iter, t, b);
        } // end if
      } // end for

      return result;
    } // end intersect()


    inline parametric parametric_at(triangle_iterator tri, const barycentric &b) const
    {
      if(!has_parametrics()) return igloo::parametric(0.f);

      return interpolate_parametric(*tri,b);
    } // end parametric_at()


    inline normal normal_at(triangle_iterator tri, const barycentric &b) const
    {
      // XXX might want to create a face normal instead
      if(!has_normals()) return igloo::normal(0.f);

      return has_vertex_normals() ? interpolate_normal(*tri, b) : m_normals[tri - triangles_begin()];
    } // end normal_at()


    inline std::pair<vector,vector> parameteric_derivatives(triangle_iterator tri) const
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
    }


  private:
    inline parametric interpolate_parametric(const triangle &tri, const barycentric &b) const
    {
      float b0 = 1.0f - b.x - b.y;

      const parametric &p0 = m_parametrics[tri.x];
      const parametric &p1 = m_parametrics[tri.y];
      const parametric &p2 = m_parametrics[tri.z];

      return b0 * p0 + b.x * p1 + b.y * p2;
    } // end interpolate_parametric()


    inline normal interpolate_normal(const triangle &tri, const barycentric &b) const
    {
      float b0 = 1.0f - b.x - b.y;

      const normal &n0 = m_normals[tri.x];
      const normal &n1 = m_normals[tri.y];
      const normal &n2 = m_normals[tri.z];

      return b0 * n0 + b.x * n1 + b.y * n2;
    } // end interpolate_normal()


    std::vector<point>      m_points;
    std::vector<parametric> m_parametrics;
    std::vector<normal>     m_normals;
    std::vector<triangle>   m_triangles;
};


} // end igloo

