#ifndef NBO_THREADER_H
#define NBO_THREADER_H

#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

template <typename Fer> class Threader final {
public:
private:
  Fer fer;
  std::atomic<bool> stop;
  std::thread th;

public:
  void run() {
    std::cout << "th run" << std::endl;
    fer.run(stop);
  };

  // use `explicit` constructor if it has one argument to prevent accidental
  // implicit conversions
  explicit Threader(Fer fer)
      : fer(std::move(fer)), stop(false),
        th(std::thread(&Threader::run, this)){};

  ~Threader() {
    stop = true;
    if (th.joinable()) {
      th.join();
    }
  }

  // disallow all these
  Threader(const Threader &p) = delete;
  Threader(Threader &&p) = delete;
  Threader &operator=(const Threader &p) = delete;
  Threader &operator=(Threader &&p) = delete;
};

#endif
