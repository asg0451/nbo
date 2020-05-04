#include "threader.h"

#include <utility>

void Threader::run() {
  std::cout << "th run" << std::endl;
  action(stop);
}

Threader::Threader(Threader::Action action)
    : stop(false), action(std::move(action)),
      th(std::thread(&Threader::run, this)){};
Threader::~Threader() {
  stop = true;
  if (th.joinable()) {
    th.join();
  }
}
