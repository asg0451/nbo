#include "space.h"
#include <random>

Space Space::make_random_space(Vec2<double> max, int n) {
  auto rd = std::random_device{};
  auto speed_x_dist = std::uniform_int_distribution<int>{-1, 1};
  auto speed_y_dist = std::uniform_int_distribution<int>{-1, 1};
  auto loc_x_dist = std::uniform_int_distribution<int>{0, int(max.x)};
  auto loc_y_dist = std::uniform_int_distribution<int>{0, int(max.y)};
  auto mass_dist = std::uniform_int_distribution<int>{1, 20};

  auto planets = std::vector<Planet>();
  planets.reserve(n);
  for (int i = 0; i < n; i++) {
    auto p =
        Planet{Vec2<double>{double(speed_x_dist(rd)), double(speed_y_dist(rd))},
               Vec2<double>{double(loc_x_dist(rd)), double(loc_y_dist(rd))},
               double(mass_dist(rd))};
    planets.push_back(p);
  }
  return Space{0.0001, max, planets};
}

std::ostream &Space::dump(std::ostream &o) const {
  o << "Space(max = " << max << "){" << planets << "}(";
  return o << ")";
}
