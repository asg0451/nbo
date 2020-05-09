#include <iostream>
#include <vector>

template <typename E> class RingBuffer {
public:
  int max;

private:
  std::vector<E> vec; // std::array?
  int idx = 0;

public:
  explicit RingBuffer(int max) : max(max), vec(std::vector<E>{}) {
    vec.reserve(max);
  };
  explicit RingBuffer(const std::vector<E> &v) : max(v.size()), vec(vec){};
  explicit RingBuffer(std::vector<E> &&v) noexcept : max(v.size()), vec(vec){};
  RingBuffer(const RingBuffer &r) = default;
  RingBuffer(RingBuffer &&r) noexcept = default;

  ~RingBuffer() = default;
  RingBuffer &operator=(const RingBuffer &b) = default;
  RingBuffer &operator=(RingBuffer &&b) noexcept = default;

  // add element. overwrites
  void add(E el) {
    idx = (idx + 1) % max;
    if (vec.size() < size_t(max)) {
      // vec[i]= fails if i < *size*. TODO: use array or smthn
      vec.push_back(el);
    } else {
      vec.at(idx) = el;
    }
  }

  // TODO(miles): iterators. seems like a whole thing
  // https://www.justsoftwaresolutions.co.uk/cplusplus/generating_sequences.html

  // TODO(miles): move to .cpp
  // TODO(miles): type traits is callable?
  template <typename F> void for_each(F f) {
    // from idx + 1 -> idx, wraping back around
    // idx = 0, max = 100
    // from 0 + 1 % 100 = 1 -> 100 - 0 -1 = 99

    // idx = 5, vs = 5
    // from 5 + 1 % 5 = 1 -> 5 - 5 - 1 = -1

    // ifdx=20, vs=100
    // from 21 -> 100 - = 19

    auto last = idx % vec.size();
    for (size_t i = idx + 1; (i % vec.size()) != last; i++) {

      // std::cout << "rb. i=" << i << ", i%=" << i % vec.size()
      //           << ", last=" << last << ", e=" << vec[i % vec.size()]
      //           << ", idx=" << idx << ", vs=" << vec.size() << ", last=" <<
      //           last
      //           << std::endl;

      f(vec[i % vec.size()]);
    }
  }
};
