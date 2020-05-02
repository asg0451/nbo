#include "simulate_thread.h"
#include "space_printer.h"
#include "threader.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>

Threader::Action simulator_action(std::mutex &mx,
                                  std::shared_ptr<Space> space_p) {
  return [&mx, space_p](std::atomic<bool> &stop) {
    for (;;) {
      if (stop) {
        return;
      }
      {
        auto lock = std::scoped_lock(mx);
        space_p.get()->tick();
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(0));
    }
  };
}
