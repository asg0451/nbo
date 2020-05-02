#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Threader final {
public:
  typedef std::function<void(std::atomic<bool> &)> Action;

private:
  std::atomic<bool> stop;
  Action action;
  std::thread th;

public:
  void run();
  Threader(Action action);
  ~Threader();
};
