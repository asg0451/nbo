#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_THREADER_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_THREADER_H

#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Threader final {
public:
  using Action = std::function<void (std::atomic<bool> &)>;

private:
  std::atomic<bool> stop;
  Action action;
  std::thread th;

public:
  void run();
  explicit Threader(Action action);
  ~Threader();
};

#endif
