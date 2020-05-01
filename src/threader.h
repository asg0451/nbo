#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
class Threader {
  // typedef void (*action_t)(std::shared_ptr<S>, int &, std::mutex &, bool &,
  //                          ActionArgs...);

protected:
  bool stop;

public:
  std::thread th;
  // TODO: apparently this isnt kosher as it's a virtual function getting called
  // during the constructor but its getting called from the thread tho... so
  // does that make it ok or a race condition?
  virtual void action() = 0;

  void run() {
    std::cout << "th run" << std::endl;
    action();
  };

  Threader() : stop(false), th(std::thread(&Threader::run, this)){};

  ~Threader() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }
};
