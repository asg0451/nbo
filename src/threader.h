#pragma once

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

// TODO: should the type of F be concrete? or a func ptr so that no captures are
// allowed? the way it is now the user just has to know that this will be
// threaded and not to capture things that could cause races. if this can even
// work

class Threader final {
public:
  typedef std::function<void(std::atomic<bool> &)> Action;
  // typedef void(Action)(std::atomic<bool> &);

private:
  std::atomic<bool> stop;
  Action &action;

public:
  void run() {
    std::cout << "th run" << std::endl;
    action(stop);
  };

  std::thread th;

  // Threader(Action &action)
  //     : stop(false), action(action), th(std::thread(&Threader::run, this)){};

  // template <typename T, typename = typename std::enable_if<
  //                           std::is_constructible<Action, T>::value>::type>
  // Threader(T &&a) : action(std::forward<T>(a)) {}

  Threader(Action &action)
      : stop(false), action(action), th(std::thread(&Threader::run, this)){};
  Threader(Action &&action)
      : stop(false), action(action), th(std::thread(&Threader::run, this)){};

  ~Threader() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }
};
