#pragma once

// XXX eliminate this upon c++14

#include <memory>

namespace igloo
{


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
} // end make_unique()


} // end igloo

