#include "space_stats.h"
#include "util.h"

#include <math.h>

void SpaceStats::log_speed(double speed) {
  if (speed > max_speed) {
    max_speed = speed;
  }
}

void SpaceStats::log_distance(double distance) {
  if (distance < min_distance) {
    min_distance = distance;
  }
}

void SpaceStats::log_tick() { ticks++; }

std::string SpaceStats::print() const {
  return util::string_format("max speed: %d, min_distance: %d, ticks: %i ",
                             max_speed, min_distance, ticks);
  ;
}

std::ostream &SpaceStats::dump(std::ostream &o) const {
  return o << util::string_format("max speed: %f, min_distance: %f, ticks: %d ",
                                  max_speed, min_distance, ticks);
  ;
}
