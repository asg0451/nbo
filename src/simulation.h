#ifndef NBO_SIMULATION_H
#define NBO_SIMULATION_H

#include <utility>

#include "simulation_stats.h"
#include "space.h"

class Simulation {
  double dt = 0.1; // sec
  Space &space;

public:
  std::unique_ptr<SimulationStats> stats = std::make_unique<SimulationStats>();
  // see comment in sim/ren thread about google's style re pointers and
  // non-const refs
  Simulation(double dt, Space *space) : dt(dt), space(*space) {}
  Simulation(double dt, Space *space, std::unique_ptr<SimulationStats> stats)
      : dt(dt), space(*space), stats(std::move(stats)) {}
  void tick();
};

#endif
