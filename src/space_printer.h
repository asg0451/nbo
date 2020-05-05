#ifndef NBO_SPACE_PRINTER_H
#define NBO_SPACE_PRINTER_H

#include "ring_buffer.h"
#include "space.h"
#include "vec2.h"

class SpacePrinter {
  inline static std::string cursor_visible = "\x1B[?25h";
  inline static std::string cursor_invisible = "\x1B[?25l";

  static std::string cursor_move(int x, int y);

  RingBuffer<Vec2<double>> breadcrumbs;

public:
  // TODO moved this to public so i could use it elsewhere. this means it doesnt
  // belong here
  inline static std::string clear = "\33[2J";

  static std::string pretty_print(const Space &space, int width = 100,
                                  int height = 46);
  static std::string pretty_print_term(const Space &space, int width = 100,
                                       int height = 46);

  std::string pretty_print_with_breadcrumbs(const Space &space, int width = 100,
                                            int height = 46);

  SpacePrinter(int num_breadcrumbs)
      : breadcrumbs(RingBuffer<Vec2<double>>{num_breadcrumbs}) {}

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
