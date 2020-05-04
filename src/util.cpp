#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h> // ioctl() and TIOCGWINSZ
#include <typeinfo>    // typeid
#include <unistd.h>    // for STDOUT_FILENO
#include <unordered_map>
#include <vector>

#include "vec2.h"

// TODO(miles): implementations are scattered between here and util.h to make it link.
// idk why. figure out

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

namespace util {
Vec2<int> get_terminal_dimensions() {
  struct winsize size{};
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  auto width = size.ws_col, height = size.ws_row;
  return Vec2<int>{width, height};
}
} // namespace util
