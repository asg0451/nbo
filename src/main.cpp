// http://physics.princeton.edu/~fpretori/Nbody/intro.htm

#include <algorithm> // transform
#include <csignal>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "planet.h"
#include "real_values.h"
#include "render_thread.h"
#include "simulate_thread.h"
#include "space.h"
#include "threader.h"
#include "util.h"
#include "vec2.h"

std::atomic<bool> quit(false); // signal flag

void pls_quit(int /*unused*/) { quit.store(true); }

int main() {
  std::signal(SIGINT, pls_quit);
  srand(time(nullptr));

  auto solar_system_dimensions =
      Vec2<double>{1000 * nasa_radius_factor, 500 * nasa_radius_factor};
  auto sun =
      Planet{solar_system_dimensions / 2, Vec2<double>::zero(), mass_of_sun};
  auto planets = std::vector<Planet>{sun};
  std::transform(real_planets.begin(), real_planets.end(),
                 std::back_inserter(planets), [&sun](auto p) {
                   auto loc = Vec2<double>{p.orbit_radius, 0} + sun.loc;
                   auto vel = Vec2<double>{0, p.orbit_speed};
                   return Planet{loc, vel, p.mass};
                 });
  auto solar_system = Space{solar_system_dimensions, planets};
  auto space_p = std::make_shared<Space>(solar_system);

  {
    auto mx = std::mutex{};
    auto renderer = Threader{renderer_action(mx, space_p, 100)};
    auto simulator = Threader{simulator_action(mx, space_p, 0, 10)};

    for (;;) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      if (quit.load()) {
        break;
      }
    }
  }

  std::cout << std::endl;
  // TODO: this doesnt print stats anymore
  space_p->dump(std::cout);
  std::cout << std::endl;

  return 0;
}

// // JSON for testing not used
// #include <nlohmann/json.hpp>
// // for convenience
// using json = nlohmann::json;
//   auto j = json{
//       {"x", {1, 2, 3}},
//   };
//   j["y"] = "hello";
//   auto j2 = R"(
//   {
//     "happy": true,
//     "pi": 3.141
//   }
// )"_json;

//   std::cout << j.dump(2) << std::endl;
//   return 0;
// //
