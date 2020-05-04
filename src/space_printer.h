#ifndef _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SPACE_PRINTER_H
#define _HOME_MILES_PROJ_NBO_BUILD_SRC_______SRC_SPACE_PRINTER_H

#include "space.h"

class SpacePrinter {
  inline static std::string cursor_visible = "\x1B[?25h";
  inline static std::string cursor_invisible = "\x1B[?25l";
  inline static std::string clear = "\33[2J";

  static std::string cursor_move(int x, int y);

public:
  static std::string pretty_print(const Space &space, int width = 100,
                                  int height = 46);
  static std::string pretty_print_term(const Space &space, int width = 100,
                                       int height = 46);

  // TODO(miles): should this be here at all?

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
    HideCursor(const HideCursor &p) = delete;
    HideCursor(HideCursor &&p) = delete;
    HideCursor &operator=(const HideCursor &p) = delete;
    HideCursor &operator=(HideCursor &&p) = delete;
  };

  class ClearScreen {
  public:
    ~ClearScreen() {
      std::cout << std::endl << clear << std::endl;
      std::cout.flush();
    }
    ClearScreen(const ClearScreen &p) = delete;
    ClearScreen(ClearScreen &&p) = delete;
    ClearScreen &operator=(const ClearScreen &p) = delete;
    ClearScreen &operator=(ClearScreen &&p) = delete;
  };
};

#endif
