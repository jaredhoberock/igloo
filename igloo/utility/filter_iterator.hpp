#pragma once

#include <iterator>
#include <type_traits>

namespace igloo
{


template<class Predicate, class Iterator>
class filter_iterator
{
  public:
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using iterator_category = std::forward_iterator_tag;

    filter_iterator() = default;

    filter_iterator(Predicate f, Iterator i, Iterator end = Iterator())
      : predicate_(f),
        base_(i),
        end_(end)
    {
      skip_filtered_positions();
    }

    filter_iterator(Iterator i, Iterator end = Iterator())
      : filter_iterator(Predicate(), i, end)
    {}

    template<class OtherIterator,
             class = typename std::enable_if<
               std::is_convertible<OtherIterator,Iterator>::value
             >::type>
    filter_iterator(const filter_iterator<Predicate,OtherIterator>& other)
      : filter_iterator(other.predicate(), other.base(), other.end())
    {}

    Predicate predicate() const
    {
      return predicate_;
    }

    const Iterator& base() const
    {
      return base_;
    }

    const Iterator& end() const
    {
      return end_;
    }

    reference operator*() const
    {
      return *base();
    }

    filter_iterator& operator++()
    {
      if(base() != end())
      {
        ++base_;
      }

      skip_filtered_positions();

      return *this;
    }

    bool operator!=(const filter_iterator& rhs) const
    {
      return base() != rhs.base();
    }

  private:
    void skip_filtered_positions()
    {
      while(base() != end() && !predicate_(*base()))
      {
        ++base_;
      }
    }

    Predicate predicate_;
    Iterator base_;
    Iterator end_;
};


template<class Predicate, class Iterator>
filter_iterator<Predicate,Iterator> make_filter_iterator(Predicate predicate, Iterator i)
{
  return filter_iterator<Predicate,Iterator>(predicate,i);
}


} // end igloo

