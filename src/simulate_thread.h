#pragma once

#include "space.h"

#include <memory>
#include <mutex>
#include <thread>

class SimulateThread {
  std::shared_ptr<Space> sp;
  int sleep_milli;
  std::mutex &mx;

  void run();

public:
  SimulateThread(std::shared_ptr<Space> sp, int sleep_milli, std::mutex &mx)
      : sp(sp), sleep_milli(sleep_milli), mx(mx){};

  std::thread start();
};
