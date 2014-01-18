#pragma once

#include <cstddef>

namespace igloo
{


class render_progress
{
  public:
    inline render_progress()
    {
      reset(0);
    }

    inline render_progress(std::size_t expected_count)
    {
      reset(expected_count);
    }

    inline void reset(std::size_t expected_count)
    {
      m_count = 0;
      m_expected_count = expected_count; 
    }

    inline std::size_t expected_count() const
    {
      return m_expected_count;
    }

    inline std::size_t count() const
    {
      return m_count;
    }

    inline std::size_t operator+=(const std::size_t increment)
    {
      m_count += increment;

      on_progress(count(), expected_count());

      return m_expected_count;
    }

    inline std::size_t operator++(int)
    {
      return operator+=(1);
    }

    inline bool complete() const
    {
      return count() >= expected_count();
    }

  protected:
    virtual void on_progress(std::size_t current_count, std::size_t expected_count)
    {}

  private:
    std::size_t m_count;
    std::size_t m_expected_count;
};


} // end igloo

