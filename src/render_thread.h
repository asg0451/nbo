#ifndef NBO_RENDER_THREAD_H
#define NBO_RENDER_THREAD_H

#include "space.h"
#include "threader.h"

#include <memory>
#include <mutex>

// TODO: should this & SimulateThread be subclasses of something? unnecessary
// for now
class RenderThread {
  std::mutex &mx;
  std::shared_ptr<Space> space_p;
  int sleep_millis;

public:
  RenderThread(std::mutex &mx, std::shared_ptr<Space> space_p, int sleep_millis)
      : mx(mx), space_p(std::move(space_p)), sleep_millis(sleep_millis){};
  void run(std::atomic<bool> &);
};

#endif
