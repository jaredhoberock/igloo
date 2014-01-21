#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>

namespace igloo
{


class bad_optional_access : public std::logic_error
{
  public:
    inline bad_optional_access(const char *what_arg)
      : std::logic_error(what_arg)
    {}

    inline bad_optional_access(const std::string &what_arg)
      : std::logic_error(what_arg)
    {}
};


template<typename T>
class optional
{
  public:
    typedef T value_type;

    /*! Creates a new disenaged optional object.
     */
    constexpr optional()
      : m_is_engaged(false)
    {}

    /*! Copies the contained value of other, if it is engaged.
     *  \param other The other optional to copy.
     */
    optional(const optional &other)
      : m_is_engaged(false)
    {
      operator=(other);
    } // end optional::optional()

    /*! Destroys the contained value, if this is in an engaged state.
     */
    ~optional()
    {
      if(m_is_engaged)
      {
        (**this).~T();
      } // end if
    } // end optional::~optional()

    /*! Assigns the contained value the value of other, if it is engaged.
     *  \param other The other optional to assign.
     *  \return *this
     */
    optional &operator=(const optional &other)
    {
      if(other.m_is_engaged)
      {
        return operator=(*other);
      } // end if
      else if(m_is_engaged)
      {
        // destroy the contained object
        (**this).~T();
        m_is_engaged = false;
      } // end else

      return *this;
    } // end operator=()

    /*! Assigns the contained value.
     *  \param value The value to assign.
     *  \return *this
     */
    template<typename U>
    optional &operator=(U &&value)
    {
      if(m_is_engaged)
      {
        operator*() = std::forward<U>(value);
      } // end if
      else
      {
        new(operator->()) T(std::forward<U>(value));
        m_is_engaged = true;
      } // end else

      return *this;
    } // end operator=()


    /*! \return A pointer to the contained value.
     *  \note The behavior is undefined if *this is in a disengaged state.
     */
    constexpr const T* operator->() const
    {
      return reinterpret_cast<const T*>(&m_data);
    } // end operator->()

    /*! \return A pointer to the contained value.
     *  \note The behavior is undefined if *this is in a disengaged state.
     */
    T* operator->()
    {
      return reinterpret_cast<T*>(&m_data);
    } // end operator->()

    /*! \return A reference to the contained value.
     *  \note The behavior is undefined if *this is in a disengaged state.
     */
    constexpr const T &operator*() const
    {
      return *operator->();
    } // end operator->()

    /*! \return A reference to the contained value.
     *  \note The behavior is undefined if *this is in a disengaged state.
     */
    T &operator*()
    {
      return *operator->();
    } // end operator->()

    /*! \return true if *this is in an engaged state; false, otherwise.
     */
    constexpr explicit operator bool () const
    {
      return m_is_engaged;
    } // end operator bool ()

    /*! \return A reference to the contained value.
     *  \throws A bad_optional_access exception if *this is in a disengaged state.
     */
    constexpr const T &value() const
    {
      if(!m_is_engaged)
      {
        throw bad_optional_access("optional is not engaged");
      } // end if

      return operator*();
    } // end value()

    /*! \return A reference to the contained value.
     *  \throws A bad_optional_access exception if *this is in a disengaged state.
     */
    T &value()
    {
      if(!m_is_engaged)
      {
        throw bad_optional_access("optional is not engaged");
      } // end if

      return operator*();
    } // end value()

    /*! \return The contained value if *this is in an engaged state; otherwise returns value.
     */
    template<typename U>
    constexpr T value_or(U &&value) const
    {
      if(!m_is_engaged) return value;
      return *m_data;
    } // end value_or()

  private:
    bool m_is_engaged;
    typename std::aligned_storage<sizeof(T),alignof(T)>::type m_data;
}; // end optional


template<typename T>
constexpr optional<typename std::decay<T>::type> make_optional(T &&value)
{
  return optional<typename std::decay<T>::type>(std::forward<T>(value));
} // end make_optional()



} // end igloo

