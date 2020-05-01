#include "render_thread.h"
#include "space_printer.h"

#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <string>
#include <thread>

#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h>    // for STDOUT_FILENO
// ...

void RenderThread::run() {
  // get terminal dimensions
  struct winsize size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
  auto width = size.ws_col, height = size.ws_row;

  auto hc = SpacePrinter::HideCursor{}; // RAII

  for (;;) {
    if (stop) {
      return;
    }
    {
      auto lock = std::scoped_lock(mx);
      std::cout << SpacePrinter::pretty_print_term(*sp.get(), width, height);
      std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}
