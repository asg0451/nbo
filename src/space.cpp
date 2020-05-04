#include "space.h"
#include "util.h"

Space Space::make_random_space(Vec2<double> max, int n) {
  auto planets = std::vector<Planet>();
  planets.reserve(n);
  for (int i = 0; i < n; i++) {
    auto p = Planet{
        Vec2<double>{1.0 * (rand() % int(max.x)), 1.0 * (rand() % int(max.y))},
        Vec2<double>{1.0 * ((rand() % 2) - 1), 1.0 * ((rand() % 2) - 1)},
        1.0 * (rand() % 20) + 1};
    planets.push_back(p);
  }
  return Space{0.0001, max, planets};
}

std::ostream &Space::dump(std::ostream &o) const {
  o << "Space(max = " << max << "){" << planets << "}(";
  return o << ")";
}
