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

#ifndef WT_IO_UTILS_H
#define WT_IO_UTILS_H

#include <stdint.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cassert>
#include <iostream>

namespace io_utils {

  // test whether a file exists or not
  inline bool exists(const char *filename) {
    struct stat st;
    return !stat(filename, &st);
  }


  // Variable-length read and write routines for unsigned numbers.
  size_t vl_write(std::ostream& out, unsigned long long size);
  unsigned long long vl_read(std::istream& in);


  /// Endian-agnostic write for integer types. This doesn't compress
  /// like vl_write, but it handles signs.
  template<class T>
  size_t write_generic(std::ostream& out, T num) {
    for (size_t i=0; i < sizeof(T); i++) {
      unsigned char lo_bits = (num & 0xFF);
      out.write((char*)&lo_bits, 1);
      num >>= 8;
    }
    return sizeof(T);
  }


  /// Endian-agnostic read for integer types. This doesn't compress
  /// like vl_write, but it handles signs.
  template<class T>
  T read_generic(std::istream& in) {
    T num = 0;
    for (size_t i=0; i < sizeof(T); i++) {
      unsigned char byte;
      in.read((char*)&byte, 1);
      num |= ((T)byte) << (i<<3);
    }
    return num;
  }
} //namespace

#endif // WT_IO_UTILS_H
