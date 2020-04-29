#pragma once

#include "space.h"

class SpacePrinter {
  Space &space;

public:
  SpacePrinter(Space &s) : space(s){};

  std::string pretty_print() const;
  std::ostream &dump(std::ostream &o) const;
};

std::ostream &operator<<(std::ostream &o, const SpacePrinter &s);
