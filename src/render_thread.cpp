#include "render_thread.h"
#include "space_printer.h"

#include <chrono>
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

  // TODO: it doesnt call destructor when you abort the thread
  // https://thispointer.com/c11-how-to-stop-or-terminate-a-thread/
  auto hc = SpacePrinter::HideCursor{}; // RAII

  for (;;) { // no exit case. kill me when done
    {
      auto lock = std::scoped_lock(mx);
      std::cout << SpacePrinter::pretty_print_term(*sp.get(), width, height);
      std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}

std::thread RenderThread::start() {
  return std::thread(&RenderThread::run, this);
}
