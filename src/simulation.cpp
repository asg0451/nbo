#include "simulation.h"

// naive & shitty, n^2 in space & time
void Simulation::tick() {
  // apply velocities
  for (auto &p : space.planets) {
    p.loc += p.vel * dt;
  }

  // build acceleration map
  auto accels = std::unordered_map<int, Vec2<double>>{};
  accels.reserve(std::pow(space.planets.size(), 2));

  for (const auto &p1 : space.planets) {
    stats.log_speed(p1.vel.mag());

    for (const auto &p2 : space.planets) {
      if (p1 == p2) {
        continue;
}

      auto distance = p2.loc.distance(p1.loc);

      stats.log_distance(distance);

      // newton
      auto f_s = space.G * p1.mass * p2.mass / std::pow(distance, 2);
      // turn that into a vector
      auto fv = (p2.loc - p1.loc).unit() * f_s;
      // f/m=a
      // add to accel for p1
      // are these refs or values? assuming former
      auto cur_a =
          util::find_optional(accels, p1.id).value_or(Vec2<double>::zero());
      cur_a = cur_a + fv / p1.mass;
      accels.insert({p1.id, cur_a});
    }
  }

  // apply all accel updates
  for (auto &p : space.planets) {
    auto a = accels[p.id];
    p.vel += a * dt;
  }

  stats.log_tick();
}
