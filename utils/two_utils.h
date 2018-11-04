/* This file is part of adept-utils.
 *
 * Copyright (C)
 *  2010-2018 Lawrence Livermore National Laboratories, United States of America
 *
 * Written by Todd Gamblin, tgamblin@llnl.gov.
 * LLNL-CODE-417602
 *
 * See the LICENSE file in the package base directory for details.
 */

#ifndef ADEPT_TWO_UTILS_H_
#define ADEPT_TWO_UTILS_H

#include <cassert>
#include <stdint.h>

namespace two_utils {

  /// Test for integral types to make sure they're powers of two.
  template <class T>
  bool is_power_of_2(T num) {
    return !(num & (num-1));
  }

  /// Returns least power of two greater than or equal to num
  inline uint64_t ge_power_of_2(uint64_t num) {
    num--;
    num |= (num >> 1);  // these fill with ones.
    num |= (num >> 2);
    num |= (num >> 4);
    num |= (num >> 8);
    num |= (num >> 16);
    num |= (num >> 32);
    num++;
    return num;
  }

  /// Returns greatest power of two less than or equal to num
  inline uint64_t le_power_of_2(uint64_t num) {
    num |= (num >> 1);  // these fill with ones.
    num |= (num >> 2);
    num |= (num >> 4);
    num |= (num >> 8);
    num |= (num >> 16);
    num |= (num >> 32);
    return num - (num >> 1);
  }

  /// Takes the log base 2 of a power of 2, returns a char.
  /// Returns -1 if 0 is passed in.
  inline signed char log2_pow2(unsigned long long powerOf2) {
    // make sure it's a power of 2.
    assert(is_power_of_2(powerOf2));

    signed char n = -1;
    while (powerOf2 > 0) {
      powerOf2 >>= 1;
      n++;
    }

    return n;
  }

  /// Inline function to determine if a number is divisible by 2.
  inline bool even(uint64_t num) {
    return !(num & 1);
  }

  /// Inline function to determine if a number is divisible by 2.
  inline bool odd(uint64_t num) {
    return (num & 1);
  }

  /// Return number of times a number is divisible by 2
  /// NOTE: This returns 0 for odd numbers AND for 0.
  /// TODO: Possibly optimize using __builtin_ctz if it's available.
  inline int times_divisible_by_2(uint64_t n) {
    if (n == 0) return 0;

    size_t count;
    for (count=0; !(n & 1); count++) {
      n >>= 1;
    }
    return count;
  }

} // namespace nami

#endif // ADEPT_TWO_UTILS_H
