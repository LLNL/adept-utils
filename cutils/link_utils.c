/* This file is part of adept-utils.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the disclaimer below.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the disclaimer (as noted below) in the
 *   documentation and/or other materials provided with the distribution.
 * - Neither the name of the LLNS/LLNL nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY, LLC,
 * THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Additional BSD Notice:
 *
 * 1. This notice is required to be provided under our contract with the U.S.
 *    Department of Energy (DOE). This work was produced at Lawrence Livermore
 *    National Laboratory under Contract No. DE-AC52-07NA27344 with the DOE.
 *
 * 2. Neither the United States Government nor Lawrence Livermore National
 *    Security, LLC nor any of their employees, makes any warranty, express or
 *    implied, or assumes any liability or responsibility for the accuracy,
 *    completeness, or usefulness of any information, apparatus, product, or
 *    process disclosed, or represents that its use would not infringe
 *    privately-owned rights.
 *
 * 3. Also, reference herein to any specific commercial products, process, or
 *    services by trade name, trademark, manufacturer or otherwise does not
 *    necessarily constitute or imply its endorsement, recommendation, or
 *    favoring by the United States Government or Lawrence Livermore National
 *    Security, LLC. The views and opinions of authors expressed herein do not
 *    necessarily state or reflect those of the United States Government or
 *    Lawrence Livermore National Security, LLC, and shall not be used for
 *    advertising or product endorsement purposes.
 *
 *
 * Copyright (c) 2010-2015, Lawrence Livermore National Security, LLC.
 * Written by Todd Gamblin, tgamblin@llnl.gov.
 * LLNL-CODE-417602
 * All rights reserved.
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
