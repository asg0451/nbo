#pragma once

#include "space.h"
#include "space_printer.h"

#include <memory>
#include <mutex>
#include <thread>

class RenderThread {
  std::shared_ptr<Space> sp;
  int sleep_milli;
  std::mutex &mx;

  void run();

public:
  RenderThread(std::shared_ptr<Space> sp, int sleep_milli, std::mutex &mx)
      : sp(sp), sleep_milli(sleep_milli), mx(mx){};

  std::thread start();
};
