#pragma once

#include <type_traits>

// The IGLOO_REQUIRES() macro may be used in a function template's parameter list
// to simulate Concepts.
//
// For example, to selectively enable a function template only for integer types,
// we could do something like this:
//
//     template<class Integer,
//              IGLOO_REQUIRES(std::is_integral<Integer>::value)
//             >
//     Integer plus_one(Integer x)
//     {
//       return x + 1;
//     }
//
#define IGLOO_REQUIRES(...) typename std::enable_if<__VA_ARGS__>::type* = nullptr

