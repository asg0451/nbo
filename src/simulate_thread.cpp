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

void SimulateThread::run(std::atomic<bool> &stop) {
  //
  auto sim = disable_stats ? Simulation{dt, space_p.get(),
                                        std::make_unique<NopSimulationStats>()}
                           : Simulation{dt, space_p.get()};
  for (;;) {
    if (stop) {
      sim.stats->dump(std::cout);
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
}
