#pragma once

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeinfo> // typeid
#include <unordered_map>
#include <vector>

// print an int vector - for convenience. this is probably a really bad idea..
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
std::ostream &operator<<(std::ostream &o, const std::unordered_map<K, V> &map) {
  // o << "Map<" << typeid(K).name() << ", " << typeid(V).name() << ">(";
  o << "{";
  for (auto &e : map) {
    o << e.first << ": " << e.second << ", ";
  }
  o << "}";
  return o;
}

// this returns a value not a ref i think..
template <typename K, typename V>
std::optional<V> find_optional(const std::unordered_map<K, V> &map, K k) {
  auto t = map.find(k);
  if (t == map.end())
    return std::nullopt;
  // return std::optional<std::reference_wrapper<V>>{t->second};
  return std::optional{t->second};
}
