#include "render_thread.h"
#include "simulation.h"
#include "space_printer.h"
#include "threader.h"

#include <memory>
#include <mutex>
#include <thread>

Threader::Action renderer_action(std::mutex &mx, std::shared_ptr<Space> space_p,
                                 int sleep_millis) {
  return [&mx, space_p, sleep_millis](std::atomic<bool> &stop) {
    // TODO: print without changing aspet ratio
    auto dim = util::get_terminal_dimensions();

    auto hc = SpacePrinter::HideCursor{};
    auto cs = SpacePrinter::ClearScreen{};

    auto sp = SpacePrinter{10000};

    for (;;) {
      if (stop) {
        return;
      }
      {
        auto lock = std::scoped_lock(mx);
        std::cout << sp.clear + sp.pretty_print_with_breadcrumbs(*space_p.get(),
                                                                 dim.x, dim.y);
        // TODO: i want to show the space stats in the top persistently. that
        // means they have to be shared, not sim thread local
        std::cout.flush();
      }
      if (sleep_millis > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_millis));
      }
    }
  };
}
