#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
template <typename F> class Threader {
  // typedef void (*action_t)(std::shared_ptr<S>, int &, std::mutex &, bool &,
  //                          ActionArgs...);

  volatile bool stop; // TODO: should be atomic bool
  F action;

public:
  void run() {
    std::cout << "th run" << std::endl;
    action(stop);
  };

  std::thread th;

  Threader(F action)
      : stop(false), action(action), th(std::thread(&Threader::run, this)){};

  ~Threader() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }
};
