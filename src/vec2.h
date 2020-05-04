#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_VEC2_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_VEC2_H

#pragma once

#include <cmath>
#include <iostream>

// TODO(miles): how to use type traits to make this only work for primitives.
// is_arithemetic, <type_traits>

// TODO(miles): move out impl

template <typename T> class Vec2 {
public:
  T x, y;
  // default constuctors

  double distance(const Vec2 &o) const {
    return std::abs(std::sqrt(std::pow(o.x - x, 2) + std::pow(o.y - y, 2)));
  }

  double mag() const {
    return std::abs(std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
  }

  Vec2<T> operator+(const Vec2<T> &o) const {
    auto v = Vec2<T>{*this};
    v.x += o.x;
    v.y += o.y;
    return v;
  }

  Vec2<T> operator+(const T &t) const {
    auto v = Vec2<T>{*this};
    v.x += t;
    v.y += t;
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

  Vec2<T> unit() const {
    auto v = Vec2<T>{*this};
    auto m = mag();
    v.x /= m;
    v.y /= m;
    return v;
  }

  static Vec2<T> zero() { return Vec2<T>{0, 0}; }
};

template <typename T>
std::ostream &operator<<(std::ostream &o, const Vec2<T> &v) {
  return o << "Vec2{" << v.x << ", " << v.y << "}";
}

#endif
