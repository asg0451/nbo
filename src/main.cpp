// http://physics.princeton.edu/~fpretori/Nbody/intro.htm

#include <csignal>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "planet.h"
#include "render_thread.h"
#include "simulate_thread.h"
#include "space.h"
#include "util.h"
#include "vec2.h"

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

std::atomic<bool> quit(false); // signal flag

void pls_quit(int) { quit.store(true); }

int main() {

  std::signal(SIGINT, pls_quit);

  // srand(time(NULL));
  // auto space = Space::make_random_space({200, 100}, 3);

  auto space =
      Space{0.0001,
            {200, 100},
            std::vector<Planet>{
                Planet{{50, 60}, {0, 0}, 20}, Planet{{60, 60}, {1, -1}, 10},
                Planet{{40, 20}, {0, .7}, 10}, Planet{{45, 25}, {.2, 0}, 10},
                // Planet{{20, 20}, {0, 0}, 10000000000}, // why doesnt this
                // suck everything in?
            }};

  auto space_p = std::make_shared<Space>(space);

  // run thread: call tick as fast as possible
  // render thread: every so often, print
  // mutex between them so you dont draw a partial state

  auto mx = std::mutex{};

  // TODO: make a superclass for these
  auto simulator = SimulateThread{space_p, 0, mx};
  auto renderer = RenderThread{space_p, 10, mx};

  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (quit.load()) {
      std::cout << "stopping.." << std::endl;
      break;
    }
  }

  return 0;
}
