#pragma once

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <igloo/utility/optional>

namespace igloo
{


using nullopt_t = std::experimental::nullopt_t;
constexpr nullopt_t nullopt{};

using in_place_t = std::experimental::in_place_t;
constexpr in_place_t in_place{};

using bad_optional_access = std::experimental::bad_optional_access;

template<class T>
using optional = std::experimental::optional<T>;

using std::experimental::make_optional;


} // end igloo

