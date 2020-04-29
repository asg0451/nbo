#include "space_printer.h"

std::string SpacePrinter::pretty_print(Space &space) {
  int width = 100, height = 44;
  // int width = 10, height = 10;
  double scale_x = 1.0 * width / space.max.x,
         scale_y = 1.0 * height / space.max.y;

  auto slots = std::vector<std::string>{}; // r-c format
  slots.assign(width * height, " ");

  for (auto p : space.planets) {
    auto x = std::floor(p.loc.x * scale_x);
    auto y = std::floor(p.loc.y * scale_y);
    auto idx = y * width + x;

    if (idx < 0 || idx > slots.size() || x > width || y > height) {
      // offscreen
      // std::cout << "tried to access" << idx << std::endl;
    } else {
      if (slots[idx] != " ") {
        slots[idx] = "*";
      } else {
        slots[idx] = std::to_string(p.id);
      }
    }
  }

  auto r = std::string{};
  r.reserve(width * height); // too lazy to do the math

  for (std::size_t i = 0; i < slots.size(); i++) {
    r += slots[i];
    if (i % width == width - 1)
      r += "|\n|";
  }

  return r;
}
