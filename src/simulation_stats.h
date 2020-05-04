#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SIMULATION_STATS_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SIMULATION_STATS_H

#include <cmath>
#include <iostream>
#include <string>

class SimulationStats {
  double max_speed = 0;
  double min_distance = INFINITY;
  int ticks = 0;

public:
  void log_speed(double /*speed*/);
  void log_distance(double /*distance*/);
  void log_tick();

  std::string print() const;
  std::ostream &dump(std::ostream &o) const;
};

#endif
