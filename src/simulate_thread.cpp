#include "simulate_thread.h"
#include "space_printer.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>

void SimulateThread::run() {
  for (;;) { // no exit case. kill me when done
    {
      auto lock = std::scoped_lock(mx);
      sp.get()->tick();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}

// TODO: this could be pulled out. a startable/runnable thread object?
std::thread SimulateThread::start() {
  return std::thread(&SimulateThread::run, this);
}
