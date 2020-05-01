#include "simulate_thread.h"
#include "space_printer.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>

void SimulateThread::run() {
  for (;;) {
    if (stop) {
      return;
    }
    {
      auto lock = std::scoped_lock(mx);
      sp.get()->tick();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}
