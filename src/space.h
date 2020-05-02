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
  const double G = 1; // for simplicity
  // const double G = 6.674 * std::pow(10, -11);
  double dt = 0.1; // sec

public:
  Vec2<int> max;
  std::vector<Planet> planets;
  SpaceStats stats = SpaceStats{};

  Space(Vec2<int> max, std::vector<Planet> planets)
      : max(max), planets(planets){};

  Space(double dt, Vec2<int> max, std::vector<Planet> planets)
      : dt(dt), max(max), planets(planets){};

  void tick();

  static Space make_random_space(Vec2<int> max, int n);

  std::ostream &dump(std::ostream &o) const;
};
