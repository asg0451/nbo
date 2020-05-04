#pragma once

#include "simulation_stats.h"
#include "space.h"

class Simulation {
  double dt = 0.1; // sec
  Space &space;
  SimulationStats stats = SimulationStats{};

public:
  Simulation(double dt, Space &space) : dt(dt), space(space) {}
  void tick();
};
