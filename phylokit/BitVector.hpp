#ifndef BITVECTOR_HPP__
#define BITVECTOR_HPP__

#include <inttypes.h>
#include <cstdlib>
#include <string>

typedef uint64_t elem_type;

class BVFIterator;

class BitVectorFixed {

 public:
  size_t size;

  BitVectorFixed(size_t size);
  BitVectorFixed(const BitVectorFixed &other);
  ~BitVectorFixed();
  BitVectorFixed &operator=(const BitVectorFixed &other);
  void resize(size_t sz);

  void set(int i);
  void unset(int i);
  bool get(int i) const;
  int ffs() const;
  int popcount() const;
  size_t hash() const;
  int overlap_size(const BitVectorFixed &other) const;

  std::string str() const;

  BVFIterator begin() const;
  BVFIterator end() const;

  void do_swap(BitVectorFixed &other);

  bool operator==(const BitVectorFixed &other) const;
  bool operator!=(const BitVectorFixed &other) const;
  BitVectorFixed operator&(const BitVectorFixed &other) const;
  BitVectorFixed &operator&=(const BitVectorFixed &other);
  BitVectorFixed operator|(const BitVectorFixed &other) const;
  BitVectorFixed &operator|=(const BitVectorFixed &other);
  BitVectorFixed operator^(const BitVectorFixed &other) const;
  BitVectorFixed &operator^=(const BitVectorFixed &other);
  BitVectorFixed operator~() const;

  friend void swap(BitVectorFixed &lhs, BitVectorFixed &rhs) {
    lhs.do_swap(rhs);
  }

 private:
  elem_type *data;
  size_t cap;

};

namespace std {
template<>
struct hash<BitVectorFixed> {
  size_t operator()(const BitVectorFixed &bvf) const {
    return bvf.hash();
  }
};
}

class BVFIterator {
  BitVectorFixed data;
  size_t cap;
  int current;
 public:
  BVFIterator() : data(1), current(-1) {}
  BVFIterator(const BitVectorFixed &data) : data(data) {

    increment();

  }
  BVFIterator &operator++() {
    increment();
    return *this;
  }
  void increment();
  int operator*() {
    return current;
  }
  bool operator!=(const BVFIterator &other) {
    return (current != other.current);
  }
  bool operator==(const BVFIterator &other) {
    return (current == other.current);
  }
};

#endif
