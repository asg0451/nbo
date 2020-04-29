// http://physics.princeton.edu/~fpretori/Nbody/intro.htm

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <cstdlib> // for clear screen

#include "planet.h"
#include "space.h"
#include "util.h"
#include "vec2.h"

int main() {
  srand(time(NULL));
  auto nticks = 100;
  auto space = Space::make_random_space(Vec2{100, 100}, 2);
  // auto space = Space({10, 10}, std::vector<Planet>{
  //                                  Planet{{0, 0}, {0, 0}, 10},
  //                                  Planet{{0, 5}, {0, 0}, 10},
  //                              });
  std::cout << space << std::endl;
  for (auto i = 0; i < nticks; i++) {
    space.tick();
    // system("clear");
    std::cout << space << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << space.pretty_print() << std::endl;
  }
  return 0;
}
