#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SPACE_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SPACE_H

#include "planet.h"
#include "util.h"
#include "vec2.h"

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

class Space {
public:
  // *10^-11 idk why this is like this but it works
  // TODO(miles): wtf. maybe an off by one order of magniture error somewhere
  // else
  constexpr static const double G_real = 6.674 * 10e-12;

  double G = G_real;
  Vec2<double> max;
  std::vector<Planet> planets;

  Space(Vec2<double> max, std::vector<Planet> planets)
      : max(max), planets(std::move(planets)){};

  Space(double G, Vec2<double> max, std::vector<Planet> planets)
      : G(G), max(max), planets(std::move(planets)){};

  static Space make_random_space(Vec2<double> max, int n);

  std::ostream &dump(std::ostream &o) const;
};

#endif
