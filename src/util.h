#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_UTIL_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_UTIL_H

#pragma once

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "vec2.h"

// print a vector - for convenience
template <typename E>
std::ostream &operator<<(std::ostream &o, const std::vector<E> &vec) {
  o << "Vector<" << typeid(E).name() << ">(";
  for (auto &e : vec) {
    o << e << ", ";
  }
  o << ")";
  return o;
}

// print an unorderd map
template <typename K, typename V>
std::ostream &operator<<(std::ostream &, const std::unordered_map<K, V> &);

namespace util {
// this returns a value not a ref i think..
template <typename K, typename V>
std::optional<V> find_optional(const std::unordered_map<K, V> &map, K k) {
  auto t = map.find(k);
  if (t == map.end()) {
    return std::nullopt;
}
  // return std::optional<std::reference_wrapper<V>>{t->second};
  return std::optional{t->second};
}

template <typename... Args>
std::string string_format(const std::string &format, Args... args) {
  size_t size =
      snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
  if (size <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(),
                     buf.get() + size - 1); // We don't want the '\0' inside
}

Vec2<int> get_terminal_dimensions();
} // namespace util

#endif
