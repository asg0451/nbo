#pragma once

#include "space.h"
#include "space_printer.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>

#include "threader.h"

class RenderThread : Threader {
  std::mutex &mx;
  std::shared_ptr<Space> space_p;
  int sleep_millis;

public:
  RenderThread(std::mutex &mx, std::shared_ptr<Space> space_p, int sleep_millis)
      : mx(mx), space_p(space_p), sleep_millis(sleep_millis){};

  void action() {
    auto dim = util::get_terminal_dimensions();
    auto hc = SpacePrinter::HideCursor{}; // RAII

    for (;;) {
      if (stop) {
        return;
      }
      {
        auto lock = std::scoped_lock(mx);
        std::cout << SpacePrinter::pretty_print_term(*space_p.get(), dim.x,
                                                     dim.y);
        std::cout.flush();
      }
      if (sleep_millis > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_millis));
    }
  }
};
