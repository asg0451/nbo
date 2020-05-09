#include "simulation.h"

#include <algorithm>
#include <iterator>

// naive & shitty, n^2 in space & time
void Simulation::tick() {
  // apply velocities
  for (auto &p : space.planets) {
    p.loc += p.vel * dt;
  }

  // build acceleration map
  // small so use array
  auto accels = std::make_unique<Vec2<double>[]>(space.planets.size());

  for (const auto &p1 : space.planets) {
    stats->log_speed(p1.vel.mag());

    for (const auto &p2 : space.planets) {
      if (p1 == p2) {
        continue;
      }

      auto distance = p2.loc.distance(p1.loc);

      stats->log_distance(distance);

      // newton
      auto f_s = space.G * p1.mass * p2.mass / std::pow(distance, 2);
      // turn that into a vector
      auto fv = (p2.loc - p1.loc).unit() * f_s;
      // f/m=a
      // add to accel for p1
      auto cur_a = accels[p1.id];
      cur_a = cur_a + fv / p1.mass;
      accels[p1.id] = cur_a;
    }
  }

  for (auto &p : space.planets) {
    p.vel += accels[p.id] * dt;
  }

  stats->log_tick();
}
