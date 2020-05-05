#include "simulation_stats.h"
#include "util.h"

#include <cmath>

void SimulationStats::log_speed(double speed) {
  if (speed > max_speed) {
    max_speed = speed;
  }
}

void SimulationStats::log_distance(double distance) {
  if (distance < min_distance) {
    min_distance = distance;
  }
}

void SimulationStats::log_tick() {
  ticks++;
  if (ticks % ticks_per_time_sample == 0) {
    log_tick_time();
  }
}

void SimulationStats::log_tick_time() {
  auto now = std::chrono::system_clock::now();
  auto dur = now - last_time;
  auto ns = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
  last_duration_micro = double(ns) / ticks_per_time_sample;
  last_time = now;
}

std::string SimulationStats::print() const {
  return util::string_format("max speed: %d, min_distance: %d, ticks: %i ",
                             max_speed, min_distance, ticks);
  ;
}

// TODO: add sim speed. requires sim.dt
std::ostream &SimulationStats::dump(std::ostream &o) const {
  return o << util::string_format("max speed: %f, min_distance: %f, ticks: %d, "
                                  "last_duration: %f (us)",
                                  max_speed, min_distance, ticks,
                                  last_duration_micro);
  ;
}
