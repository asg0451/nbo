#include "simulate_thread.h"
#include "simulation.h"
#include "space_printer.h"
#include "threader.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>

Threader::Action simulator_action(std::mutex *mx,
                                  std::shared_ptr<Space> space_p,
                                  int sleep_millis, double dt) {
  return [&mx, space_p, sleep_millis, dt](std::atomic<bool> &stop) {
    auto sim = Simulation{dt, *space_p.get()};
    for (;;) {
      if (stop) {
        return;
      }
      {
        auto lock = std::scoped_lock(*mx);
        sim.tick();
      }
      if (sleep_millis > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_millis));
    }
  };
}
