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

  for (;;) { // no exit case. kill me when done
    {
      auto lock = std::scoped_lock(mx);
      system("clear");
      std::cout << SpacePrinter::pretty_print(*sp.get(), width, height)
                << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_milli));
  }
}

std::thread RenderThread::start() {
  return std::thread(&RenderThread::run, this);
}
