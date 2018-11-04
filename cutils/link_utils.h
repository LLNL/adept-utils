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

#ifndef ADEPT_LINK_UTILS_H
#define ADEPT_LINK_UTILS_H
//
// Utility functions for accessing r_debug and link.h
//
#include <link.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

  /// Dumps out a string representation of the link map to the
  /// specified file descriptor.
  void dump_link_map(FILE *out);
  
  /// Uses r_debug interface in link.h to get the load module for an
  /// address.  This sorts the load addresses in the list then finds
  /// the lowest 
  /// Returns NULL if no symbols was not found in any module.
  struct link_map *get_module_for_address(void *address);

  /// Gets a module from the link map by its full path name.
  /// Returns NULL if no such module exists.
  struct link_map *get_module_by_full_path(const char *path);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif // ADEPT_LINK_UTILS_H
