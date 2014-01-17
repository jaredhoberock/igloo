#pragma once

#include <vector>
#include <algorithm>

namespace igloo
{


template<typename T>
  class array2
{
  private:
    typedef std::vector<T> storage_type;

  public:
    typedef typename storage_type::value_type        value_type;
    typedef typename storage_type::pointer           pointer;
    typedef typename storage_type::const_pointer     const_pointer;
    typedef typename storage_type::reference         reference;
    typedef typename storage_type::const_reference   const_reference;
    typedef typename storage_type::size_type         size_type;
    typedef typename storage_type::iterator          iterator;
    typedef typename storage_type::const_iterator    const_iterator;

    array2(size_type width, size_type height)
      : m_data(width * height),
        m_width(width),
        m_height(height)
    {}

    iterator begin()
    {
      return m_data.begin();
    }

    iterator end()
    {
      return m_data.end();
    }

    const_iterator begin() const
    {
      return m_data.begin();
    }

    const_iterator end() const
    {
      return m_data.end();
    }

    pointer data()
    {
      return m_data.data();
    }

    const_pointer data() const
    {
      return m_data.data();
    }

    reference raster(size_type i, size_type j)
    {
      return m_data[j*width() + i];
    } // end raster()

    const_reference raster(size_type i, size_type j) const
    {
      return m_data[j*width() + i];
    } // end raster()

    void fill(const value_type &v)
    {
      std::fill(m_data.begin(), m_data.end(), v);
    } // end fill()

    size_type width() const
    {
      return m_width;
    } // end width()

    size_type height() const
    {
      return m_height;
    } // end width()

    size_type size() const
    {
      return m_data.size();
    } // end size()

  private:
    storage_type m_data;
    size_type m_width, m_height;
}; // end array2


} // end igloo

