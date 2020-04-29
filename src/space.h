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

  void tick();

  static Space make_random_space(Vec2<int> max, int n);

  std::ostream &dump(std::ostream &o) const;
};
