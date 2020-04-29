#include "render_thread.h"
#include "space_printer.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>

void RenderThread::run() {
  for (;;) { // no exit case. kill me when done
    {
      auto lock = std::scoped_lock(mx);
      system("clear");
      std::cout << SpacePrinter::pretty_print(*sp.get()) << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}

std::thread RenderThread::start() {
  return std::thread(&RenderThread::run, this);
}
