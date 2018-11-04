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

#define _GNU_SOURCE
#include "link_utils.h"
#include <stdlib.h>
#include <dlfcn.h>

#define printsymbol(symbol) \
  { \
    void *mysym = dlsym(RTLD_NEXT, #symbol); \
    struct link_map *map = get_module_for_address(mysym); \
    printf("module for " #symbol "(%#tx): %#tx(%s)\n", mysym, map->l_addr, map->l_name); \
  }



int main(int argc, char **argv) {
  dump_link_map(stdout);

  printsymbol(printf);
  printsymbol(malloc);
  printsymbol(dlsym);


  struct link_map *map = get_module_by_full_path("/lib64/libdl.so.2");
  if (map) {
    printf("%s\n", map->l_name);
  } else {
    printf("not found.\n");
  }

}
