#pragma once

#include "space.h"

class SpacePrinter {
  inline static std::string cursor_visible = "\x1B[?25h";
  inline static std::string cursor_invisible = "\x1B[?25l";
  inline static std::string clear = "\33[2J";

  static std::string cursor_move(int x, int y);

public:
  static std::string pretty_print(Space &, int width = 100, int height = 46);
  static std::string pretty_print_term(Space &, int width = 100,
                                       int height = 46);

  // TODO: should this be here at all?

  class HideCursor {
  public:
    HideCursor() {
      std::cout << cursor_invisible;
      std::cout.flush();
    }
    ~HideCursor() {
      std::cout << cursor_visible;
      std::cout.flush();
    }
  };
};
