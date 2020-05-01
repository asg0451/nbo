#pragma once

#include "space.h"

#include <memory>
#include <mutex>

#include "threader.h"

class SimulateThread : Threader {
  std::mutex &mx;
  std::shared_ptr<Space> space_p;
  int sleep_millis;

public:
  SimulateThread(std::mutex &mx, std::shared_ptr<Space> space_p,
                 int sleep_millis)
      : mx(mx), space_p(space_p), sleep_millis(sleep_millis){};

  void action() {
    for (;;) {
      if (stop) {
        return;
      }
      {
        auto lock = std::scoped_lock(mx);
        space_p.get()->tick();
      }
      if (sleep_millis > 0)
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_millis));
    }
  }
};
