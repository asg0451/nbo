#pragma once

#include "planet.h"
#include "util.h"
#include "vec2.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

class Space {
  const double G = 1;    // for simplicity // 6.674 * std::pow(10, -11);
  const double dt = 0.1; // sec
public:
  Vec2<int> max;
  std::vector<Planet> planets;

  Space(Vec2<int> max, std::vector<Planet> planets)
      : max(max), planets(planets){};

  // naive & shitty, n^2 in space & time
  void tick() {
    // apply velocities
    for (auto &p : planets) {
      p.loc += p.vel * dt;
    }

    // build acceleration map
    auto accels = std::unordered_map<int, Vec2<double>>{};
    accels.reserve(std::pow(planets.size(), 2));

    for (const auto &p1 : planets) {
      for (const auto &p2 : planets) {
        if (p1 == p2)
          continue;
        // newton
        auto f_s = G * p1.mass * p2.mass / std::pow(p2.loc.distance(p1.loc), 2);

        // turn that into a vector
        auto fv = (p2.loc - p1.loc).scaled() * f_s;

        // std::cout << p1 << ": "
        //           << "fv = " << fv << std::endl;

        // f/m=a
        // add to accel for p1
        // are these refs or values? assuming former. if nothing moves maybe
        // it's latter
        auto cur_a = find_optional(accels, p1.id).value_or(Vec2{0.0, 0.0});
        cur_a = cur_a + fv / p1.mass;
        accels.insert({p1.id, cur_a});
      }
    }

    // std::cout << "accels:" << accels << std::endl;
    // apply all accel updates
    for (auto &p : planets) {
      auto a = accels[p.id];
      p.vel += a * dt;
    }
  }

  // TODO: to pretty grid view thing
  /*
    ----------
    | .
    |
    |
    | .
    ---------
   */

  std::string pretty_print() const {
    int width = 100, height = 44;
    // int width = 10, height = 10;
    double scale_x = 1.0 * width / max.x, scale_y = 1.0 * height / max.y;

    auto slots = std::vector<std::string>{}; // r-c format
    slots.assign(width * height, " ");

    for (auto p : planets) {
      auto x = std::floor(p.loc.x * scale_x);
      auto y = std::floor(p.loc.y * scale_y);
      auto idx = y * width + x;

      if (idx < 0 || idx > slots.size() || x > width || y > height) {
        // offscreen
        // std::cout << "tried to access" << idx << std::endl;
      } else {
        if (slots[idx] != " ") {
          slots[idx] = "*";
        } else {
          slots[idx] = std::to_string(p.id);
        }
      }
    }

    auto r = std::string{};
    r.reserve(width * height); // too lazy to do the math

    for (std::size_t i = 0; i < slots.size(); i++) {
      r += slots[i];
      if (i % width == width - 1)
        r += "|\n|";
    }

    return r;
  }

  static Space make_random_space(Vec2<int> max, int n) {
    auto planets = std::vector<Planet>();
    planets.reserve(n);
    for (int i = 0; i < n; i++) {
      auto p = Planet{
          Vec2<double>{1.0 * (rand() % max.x / 2), 1.0 * (rand() % max.y / 2)},
          Vec2<double>{1.0 * ((rand() % 2) - 1), 1.0 * ((rand() % 2) - 1)},
          rand() % 20 + 1};
      planets.push_back(p);
    }
    return Space{max, planets};
  }
};

std::ostream &operator<<(std::ostream &o, const Space &s) {
  return o << "Space{" << s.planets << "}";
}
