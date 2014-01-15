#pragma once

#include <vector>
#include <stdexcept>
#include <igloo/geometry/vector.hpp>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class triangle_mesh
{
  public:
    typedef uint3 triangle;

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
    const point *points_data() const
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
    const parametric *parametrics_data() const
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
    const normal *normals_data() const
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
    const triangle *triangles_data() const
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

  private:
    std::vector<point>      m_points;
    std::vector<parametric> m_parametrics;
    std::vector<normal>     m_normals;
    std::vector<triangle>   m_triangles;
};


} // end igloo

