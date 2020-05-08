#ifndef NBO_SIMULATION_H
#define NBO_SIMULATION_H

#include <utility>

#include "simulation_stats.h"
#include "space.h"

class Simulation {
  double dt = 0.1; // sec
  Space &space;

public:
  SimulationStats stats = SimulationStats{};
  // see comment in sim/ren thread about google's style re pointers and
  // non-const refs
  Simulation(double dt, Space *space) : dt(dt), space(*space) {}
  Simulation(double dt, Space *space, SimulationStats stats)
      : dt(dt), space(*space), stats(std::move(stats)) {}
  void tick();
};

#endif
