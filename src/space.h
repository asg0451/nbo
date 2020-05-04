#pragma once

#include "planet.h"
#include "util.h"
#include "vec2.h"

#include <iostream>
#include <stdlib.h>
#include <unordered_map>
#include <vector>

class Space {
public:
  // *10^-11 idk why this is like this but it works
  // TODO wtf. maybe an off by one order of magniture error somewhere else
  constexpr static const double G_real = 6.674 * 10e-12;

  double G = G_real;
  Vec2<double> max;
  std::vector<Planet> planets;

  Space(Vec2<double> max, std::vector<Planet> planets)
      : max(max), planets(planets){};

  Space(double G, Vec2<double> max, std::vector<Planet> planets)
      : G(G), max(max), planets(planets){};

  static Space make_random_space(Vec2<double> max, int n);

  std::ostream &dump(std::ostream &o) const;
};
