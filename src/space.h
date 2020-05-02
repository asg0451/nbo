#pragma once

#include "planet.h"
#include "space_stats.h"
#include "util.h"
#include "vec2.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

class Space {
  double G = 1;    // for simplicity
  double dt = 0.1; // sec

public:
  constexpr static const double G_real =
      0.00000000006674; // 6.674 * std::pow(10, -11);
  Vec2<double> max;
  std::vector<Planet> planets;
  SpaceStats stats = SpaceStats{};

  Space(Vec2<double> max, std::vector<Planet> planets)
      : max(max), planets(planets){};

  Space(double dt, Vec2<double> max, std::vector<Planet> planets)
      : dt(dt), max(max), planets(planets){};

  Space(double G, double dt, Vec2<double> max, std::vector<Planet> planets)
      : G(G), dt(dt), max(max), planets(planets){};

  void tick();

  static Space make_random_space(Vec2<double> max, int n);

  std::ostream &dump(std::ostream &o) const;
};
