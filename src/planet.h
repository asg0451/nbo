#pragma once

#include "vec2.h"
#include <iostream>

class Planet {
  inline static int next_id = 0; // not thread safe but w/e

public:
  Vec2<double> loc, vel;
  double mass;
  int id;

  Planet(Vec2<double> loc, Vec2<double> vel, double mass)
      : loc(loc), vel(vel), mass(mass), id(next_id++){};
  Planet(const Planet &p)
      : loc(p.loc), vel(p.vel), mass(p.mass),
        id(p.id){}; // TODO: how can i get compiler to write this?

  bool operator==(const Planet &o) const { return id == o.id; }
};

std::ostream &operator<<(std::ostream &o, const Planet &p);
