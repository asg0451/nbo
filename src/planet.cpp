#include "planet.h"

std::ostream &operator<<(std::ostream &o, const Planet &p) {
  return o << "Planet{id=" << p.id << ", loc=" << p.loc << ", vel=" << p.vel
           << ", m=" << p.mass << "}";
}
