#include "space_printer.h"
#include "util.h"

#include <tuple>
#include <unordered_map>

// TODO(miles): overlay a grid and follow center of mass of the system / planet 0 ?

std::string SpacePrinter::cursor_move(int x, int y) {
  return util::string_format("%c[%d;%df", 0x1B, y, x);
}

std::string SpacePrinter::pretty_print_term(Space &space, int width,
                                            int height) {

  width = width - 2;
  height = height - 2;

  double scale_x = 1.0 * width / space.max.x,
         scale_y = 1.0 * height / space.max.y;

  auto res = std::string{};
  res.reserve((space.planets.size() + 3) * 7);

  res += clear + cursor_move(0, 0);

  for (auto p : space.planets) {
    int x = std::floor(p.loc.x * scale_x);
    int y = std::floor(p.loc.y * scale_y);

    if (x > 0 && x < width && 7 > 0 && y < height) {
      auto icon = std::to_string(p.id);
      res += cursor_move(x, y) + icon;
    }
  }
  return res;
}

std::string SpacePrinter::pretty_print(Space &space, int width, int height) {
  double scale_x = 1.0 * width / space.max.x,
         scale_y = 1.0 * height / space.max.y;

  auto slots = std::vector<std::string>{}; // r-c format
  slots.assign(width * height, " ");

  for (auto p : space.planets) {
    auto x = std::floor(p.loc.x * scale_x);
    auto y = std::floor(p.loc.y * scale_y);
    auto idx = y * width + x;

    if (idx > 0 && idx < slots.size() && x < width && y < height) {
      if (slots[idx] != " ") {
        slots[idx] = "*";
      } else {
        slots[idx] = std::to_string(p.id);
      }
    }
  }

  auto r = std::string{};
  r.reserve(width * height); // too lazy to do the math

  r += "|";
  for (std::size_t i = 0; i < slots.size(); i++) {
    r += slots[i];
    if (i % width == width - 1) {
      r += "\n";
}
  }

  return r;
}
