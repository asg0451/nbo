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
  using Action = std::function<void(std::atomic<bool> &)>;

private:
  std::atomic<bool> stop;
  Action action;
  std::thread th;

public:
  void run();
  explicit Threader(Action action);
  ~Threader();

  // what is this? dont allow these to happen?
  Threader(const Threader &p) = delete;
  Threader(Threader &&p) = delete;
  Threader &operator=(const Threader &p) = delete;
  Threader &operator=(Threader &&p) = delete;
};

#endif
// ../../src/threader.h:13:7: warning: class 'Threader' defines a non-default
// destructor but does not define a copy constructor, a copy assignment
// operator, a move constructor or a move assignment operator
// [hicpp-special-member-functions]
