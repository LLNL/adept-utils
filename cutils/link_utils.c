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

#include "link_utils.h"
#include <stdlib.h>
#include <string.h>

static int link_map_addr_comp(const void *l, const void *r) {
  struct link_map *lhs = (struct link_map*)l;
  struct link_map *rhs = (struct link_map*)r;

  if (lhs->l_addr == rhs->l_addr) {
    return 0;
  }
  return lhs->l_addr < rhs->l_addr ? -1 : 1;
}


static int link_map_length(struct link_map *map) {
  int len;
  for (len=0; map; map = map->l_next) {
    len++;
  }
  return len;
}


void dump_link_map(FILE *out) {
  int len = link_map_length(_r_debug.r_map);
  struct link_map *ordered_maps[len];
  struct link_map *lmap = _r_debug.r_map;
  for (int i=0; i < len; i++) {
    ordered_maps[i] = lmap;
    lmap = lmap->l_next;
  }

  qsort(ordered_maps, len, sizeof(struct link_map*), link_map_addr_comp);
  for (int i=0; i < len; i++) {
    fprintf(out, "%#-16tx    %s\n", ordered_maps[i]->l_addr, ordered_maps[i]->l_name);
  }
}


struct link_map *get_module_for_address(void *address) {
  struct link_map *module = _r_debug.r_map;
  for (struct link_map *lmap = module->l_next; lmap; lmap = lmap->l_next) {
    if (lmap->l_addr < (intptr_t)address && lmap->l_addr > module->l_addr) {
      module = lmap;
    }
  }
  return module;
}


struct link_map *get_module_by_full_path(const char *path) {
  for (struct link_map *lmap = _r_debug.r_map; lmap; lmap = lmap->l_next) {
    if (strcmp(lmap->l_name, path) == 0) {
      return lmap;
    }
  }
  return NULL;
}
