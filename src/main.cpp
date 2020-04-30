// http://physics.princeton.edu/~fpretori/Nbody/intro.htm

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

int main() {
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

  auto simulator = SimulateThread{space_p, 0, mx};
  auto sth = simulator.start();

  auto renderer = RenderThread{space_p, 10, mx};
  auto rth = renderer.start();

  rth.join();
  sth.join();

  return 0;
}
