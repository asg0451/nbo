#include "space.h"
#include "util.h"

// naive & shitty, n^2 in space & time
void Space::tick() {
  // apply velocities
  for (auto &p : planets) {
    p.loc += p.vel * dt;
  }

  // build acceleration map
  auto accels = std::unordered_map<int, Vec2<double>>{};
  accels.reserve(std::pow(planets.size(), 2));

  for (const auto &p1 : planets) {
    stats.log_speed(p1.vel.mag());

    for (const auto &p2 : planets) {
      if (p1 == p2)
        continue;

      auto distance = p2.loc.distance(p1.loc);

      stats.log_distance(distance);

      // newton
      auto f_s = G * p1.mass * p2.mass / std::pow(distance, 2);
      // turn that into a vector
      auto fv = (p2.loc - p1.loc).scaled() * f_s;
      // f/m=a
      // add to accel for p1
      // are these refs or values? assuming former
      auto cur_a =
          util::find_optional(accels, p1.id).value_or(Vec2<double>{0.0, 0.0});
      cur_a = cur_a + fv / p1.mass;
      accels.insert({p1.id, cur_a});
    }
  }

  // apply all accel updates
  for (auto &p : planets) {
    auto a = accels[p.id];
    p.vel += a * dt;
  }

  stats.log_tick();
}

Space Space::make_random_space(Vec2<int> max, int n) {
  auto planets = std::vector<Planet>();
  planets.reserve(n);
  for (int i = 0; i < n; i++) {
    auto p =
        Planet{Vec2<double>{1.0 * (rand() % max.x), 1.0 * (rand() % max.y)},
               Vec2<double>{1.0 * ((rand() % 2) - 1), 1.0 * ((rand() % 2) - 1)},
               1.0 * (rand() % 20) + 1};
    planets.push_back(p);
  }
  return Space{0.0001, max, planets};
}

std::ostream &Space::dump(std::ostream &o) const {
  o << "Space(dt = " << dt << "){" << planets << "}(";
  stats.dump(o);
  return o << ")";
}
