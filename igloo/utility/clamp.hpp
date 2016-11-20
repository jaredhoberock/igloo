#pragma once

#include <algorithm>
#include <functional>

namespace igloo
{


template<class T, class Compare>
constexpr const T& clamp(const T& value, const T& low, const T& hi, Compare comp)
{
  return comp(value, low) ? low : comp(value, hi) ? hi : value;
}


template<class T>
constexpr const T& clamp(const T& value, const T& low, const T& hi)
{
  return clamp(value, low, hi, std::less<>());
}


}

