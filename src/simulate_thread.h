#pragma once

#include "space.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>

class SimulateThread {
  std::shared_ptr<Space> sp;
  int sleep_milli;
  std::mutex &mx;
  bool stop;

  void run();

public:
  std::thread th;

  SimulateThread(std::shared_ptr<Space> sp, int sleep_milli, std::mutex &mx)
      : sp(sp), sleep_milli(sleep_milli), mx(mx), stop(false),
        th(std::thread(&SimulateThread::run, this)){

        };

  ~SimulateThread() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }
};
