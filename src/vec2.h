#pragma once

#include <cmath>
#include <iostream>

// TODO: how to use type traits to make this only work for primitives.
// is_arithemetic, <type_traits>

template <typename T> class Vec2 {
public:
  T x, y;
  // default constuctors

  double distance(const Vec2 &o) const {
    return std::abs(std::sqrt(std::pow(o.x - x, 2) + std::pow(o.y - y, 2)));
  }

  Vec2<T> operator+(const Vec2<T> &o) const {
    auto v = Vec2<T>{*this};
    v.x += o.x;
    v.y += o.y;
    return v;
  }

  Vec2<T> operator-(const Vec2<T> &o) const {
    auto v = Vec2<T>{*this};
    v.x -= o.x;
    v.y -= o.y;
    return v;
  }

  Vec2<double> &operator+=(const Vec2 &o) {
    x += o.x;
    y += o.y;
    return *this;
  }

  Vec2<T> operator/(T d) const {
    auto v = Vec2<T>{*this};
    v.x /= d;
    v.y /= d;
    return v;
  }

  Vec2<T> operator*(T d) const {
    auto v = Vec2<T>{*this};
    v.x *= d;
    v.y *= d;
    return v;
  }

  Vec2<T> scaled() const {
    auto v = Vec2<T>{*this};
    auto mag = v.distance({0, 0});
    v.x /= mag;
    v.y /= mag;
    return v;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &o, const Vec2<T> &v) {
  return o << "Vec2{" << v.x << ", " << v.y << "}";
}
