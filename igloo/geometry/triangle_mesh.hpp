#pragma once

#include <array>
#include <vector>
#include <igloo/geometry/point.hpp>
#include <igloo/geometry/parametric.hpp>
#include <igloo/geometry/normal.hpp>

namespace igloo
{


class triangle_mesh
{
  public:
    typedef std::array<unsigned int,3> triangle;

    typedef std::vector<point>::const_iterator      point_iterator;
    typedef std::vector<parametric>::const_iterator parametric_iterator;
    typedef std::vector<normal>::const_iterator     normal_iterator;
    typedef std::vector<triangle>::const_iterator   triangle_iterator;

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

    /*! \return The number of vertices.
     */
    inline std::size_t vertices_size() const
    {
      return m_points.size();
    } // end vertices_size()


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

