#include "render_thread.h"
#include "space_printer.h"
#include "util.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <string>
#include <thread>

void RenderThread::run() {
  auto dim = util::get_terminal_dimensions();
  auto hc = SpacePrinter::HideCursor{}; // RAII

  for (;;) {
    if (stop) {
      return;
    }
    {
      auto lock = std::scoped_lock(mx);
      std::cout << SpacePrinter::pretty_print_term(*sp.get(), dim.x, dim.y);
      std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}
