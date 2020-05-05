#include "simulate_thread.h"
#include "simulation.h"
#include "simulation_stats.h"
#include "space_printer.h"
#include "threader.h"

#include <chrono>
#include <cstdlib>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>

Threader::Action simulator_action(std::mutex &mx,
                                  const std::shared_ptr<Space> space_p,
                                  int sleep_millis, double dt,
                                  bool disable_stats) {
  return [&mx, space_p, sleep_millis, dt,
          disable_stats](std::atomic<bool> &stop) {
    auto sim = disable_stats
                   ? Simulation{dt, space_p.get(), NopSimulationStats{}}
                   : Simulation{dt, space_p.get()};

    for (;;) {
      if (stop) {
        sim.stats.dump(std::cout);

        return;
      }
      {
        auto lock = std::scoped_lock(mx);
        sim.tick();
      }
      if (sleep_millis > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_millis));
      }
    }
  };
}
