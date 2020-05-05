#ifndef NBO_SIMULATION_H
#define NBO_SIMULATION_H

#include "simulation_stats.h"
#include "space.h"

class Simulation {
  double dt = 0.1; // sec
  Space &space;
  SimulationStats stats = SimulationStats{};

public:
  // see comment in sim/ren thread about google's style re pointers and
  // non-const refs
  Simulation(double dt, Space *space) : dt(dt), space(*space) {}
  void tick();
};

#endif
