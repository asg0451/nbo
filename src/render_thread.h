#pragma once

#include "space.h"
#include "space_printer.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>

class RenderThread {
  std::shared_ptr<Space> sp;
  int sleep_milli;
  std::mutex &mx;
  volatile bool stop;

  void run();

public:
  std::thread th;

  RenderThread(std::shared_ptr<Space> sp, int sleep_milli, std::mutex &mx)
      : sp(sp), sleep_milli(sleep_milli), mx(mx), stop(false),
        th(std::thread(&RenderThread::run, this)){};

  ~RenderThread() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }
};
