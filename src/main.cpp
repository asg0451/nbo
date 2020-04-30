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
  // auto space = Space::make_random_space(Vec2{100, 100}, 3);

  auto space = Space{0.1,
                     {200, 80},
                     std::vector<Planet>{
                         Planet{{50, 60}, {0, 0}, 20},
                         Planet{{60, 60}, {1, -1}, 10},
                         Planet{{40, 20}, {0, .7}, 10},
                     }};

  auto space_p = std::make_shared<Space>(space);

  // run thread: call tick as fast as possible
  // render thread: every so often, print
  // mutex between them so you dont draw a partial state

  auto mx = std::mutex{};

  auto simulator = SimulateThread{space_p, 1, mx};
  auto sth = simulator.start();

  auto renderer = RenderThread{space_p, 50, mx};
  auto rth = renderer.start();

  rth.join();
  sth.join();

  return 0;
}
