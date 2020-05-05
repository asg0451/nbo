#ifndef NBO_SIMULATION_STATS_H
#define NBO_SIMULATION_STATS_H

#include <chrono>
#include <cmath>
#include <iostream>
#include <string>

class SimulationStats {
  double max_speed = 0;
  double min_distance = INFINITY;
  int ticks = 0;
  std::chrono::time_point<std::chrono::system_clock> last_time = {};
  double last_duration_micro = 0;

  inline static int ticks_per_time_sample = 1000;

  void log_tick_time();

public:
  virtual void log_speed(double /*speed*/);
  virtual void log_distance(double /*distance*/);
  virtual void log_tick();

  std::string print() const;
  std::ostream &dump(std::ostream &o) const;
};

class NopSimulationStats : public SimulationStats {
public:
  void log_speed(double /*speed*/) override {}
  void log_distance(double /*distance*/) override {}
  void log_tick() override {}

  std::string print() const { return "stats disabled"; };
  std::ostream &dump(std::ostream &o) const { return o; };
};

#endif
