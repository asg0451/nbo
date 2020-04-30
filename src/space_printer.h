#pragma once

#include "space.h"

class SpacePrinter {
public:
  static std::string pretty_print(Space &, int width = 100, int height = 46);
};
