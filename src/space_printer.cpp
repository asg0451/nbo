#include "space_printer.h"

// TODO; overlay a grid and follow center of mass of the system / planet 0 ?
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
    if (i % width == width - 1)
      r += "\n";
  }

  return r;
}
