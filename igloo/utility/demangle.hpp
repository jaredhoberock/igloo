#pragma once

#include <string>
#include <typeinfo>

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
#include <cstdlib>
#endif

namespace igloo
{


#if __has_include(<cxxabi.h>)

inline std::string demangle(const char* name)
{
  int status = -4;
  
  char* free_me = abi::__cxa_demangle(name, nullptr, nullptr, &status);
  
  const char* const demangled_name = (status==0) ? free_me : name;
  
  std::string result(demangled_name);
  
  std::free(free_me);
  
  return result;
}

#else

// we assume that platforms which do not have <cxxabi.h> do not mangle their names
inline std::string demangle(const char* name)
{
  return name;
}

#endif


inline std::string type_name(const std::type_info& info)
{
  std::string demangled = demangle(info.name());

  // to strip off leading namespaces, if any, grab everything to the right of the rightmost colon
  auto index_of_last_colon = demangled.find_last_of(":");
  if(index_of_last_colon == std::string::npos)
  {
    // no colons, just return the demangled name as-is
    return demangled;
  }

  // erase characters [0, index_of_last_colon]
  return demangled.erase(0, index_of_last_colon+1);
}


} // end igloo

