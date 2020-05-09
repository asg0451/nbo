#ifndef NBO_SIMULATE_THREAD_H
#define NBO_SIMULATE_THREAD_H

#include "space.h"
#include "threader.h"

#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>

class SimulateThread {
  std::mutex &mx;
  std::shared_ptr<Space> space_p;
  int sleep_millis;
  double dt;
  bool disable_stats = false;

public:
  SimulateThread(std::mutex &mx, std::shared_ptr<Space> space_p,
                 int sleep_millis, double dt, bool disable_stats = false)
      : mx(mx), space_p(std::move(space_p)), sleep_millis(sleep_millis), dt(dt),
        disable_stats(disable_stats){};
  void run(std::atomic<bool> & /*stop*/);
};

#endif
