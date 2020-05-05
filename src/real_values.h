#ifndef NBO_REAL_VALUES_H
#define NBO_REAL_VALUES_H

#include <string>
#include <vector>

// double v_orbit(double G, double mass_c, double r) {
//   return std::sqrt(G * mass_c / r);
// }

// from nasa fact sheet
// https://nssdc.gsfc.nasa.gov/planetary/factsheet/
// and approximated, circularized, etc
// i think its right but cant guarantee it

class SolarBodyInfo {
public:
  std::string name;
  double mass, orbit_radius, orbit_speed;
};

constexpr double nasa_mass_factor = 10e24;    // kg
constexpr double nasa_radius_factor = 10e9;   // m
constexpr double nasa_speed_factor = 1000;    // m/s
constexpr double mass_of_sun = 1.989 * 10e30; // kg

const auto real_planets = std::vector<SolarBodyInfo>{
    SolarBodyInfo{"Mercury", 0.33 * nasa_mass_factor, 57.9 * nasa_radius_factor,
                  47.4 * nasa_speed_factor},
    SolarBodyInfo{"Venus", 4.87 * nasa_mass_factor, 108.2 * nasa_radius_factor,
                  35 * nasa_speed_factor},
    SolarBodyInfo{"Earth", 5.97 * nasa_mass_factor, 149.6 * nasa_radius_factor,
                  29.8 * nasa_speed_factor},
    SolarBodyInfo{"Moon", 0.073 * nasa_mass_factor,
                  (149.6 + .384) * nasa_radius_factor,
                  (29.8 + 1) * nasa_speed_factor},
    SolarBodyInfo{"Mars", 0.642 * nasa_mass_factor, 227.9 * nasa_radius_factor,
                  24.1 * nasa_speed_factor}};

#endif
