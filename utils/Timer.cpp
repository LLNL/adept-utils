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


#include "Timer.h"

#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
using namespace std;


Timer::Timer() : t_start(get_time_ns()), t_last(t_start) { }


Timer::Timer(const Timer& other): 
  timings(other.timings),
  order(other.order),
  t_start(other.t_start),
  t_last(other.t_last) 
{ }


Timer& Timer::operator=(const Timer& other) {
  timings = other.timings;
  order = other.order;
  t_start = other.t_start;
  t_last = other.t_last;
  return *this;
}


Timer::~Timer() { }


void Timer::clear() {
  order.clear();
  timings.clear();
  t_start = get_time_ns();
  t_last = t_start;
}


void Timer::fast_forward() { 
  t_last = get_time_ns(); 
}


void Timer::record(const string& name) {
  timing_t now = get_time_ns();
  timing_t elapsed = now - t_last;

  timing_map::iterator i = timings.find(name);
  if (i == timings.end()) {
    order.push_back(name);  // track insertion order of unique keys
  }
  timings[name] += elapsed;

  t_last = now;
}

void Timer::start(const string& name) {
  fast_forward();
}

void Timer::stop(const string& name) {
  record(name);
}


Timer& Timer::operator+=(const Timer& other) {
  for (size_t i=0; i < other.order.size(); i++) {
    const string& other_name = other.order[i];
    if (timings.find(other_name) == timings.end()) {
      order.push_back(other_name);
    }
    timings[other_name] += other[other_name];
  }
  return *this;
}


void Timer::write(std::ostream& out, bool print_total) const {
  timing_t now = get_time_ns();
  const string total("Total");
  size_t max_len = total.length();

  for (size_t i=0; i < order.size(); i++) {
    max_len = max(max_len, order[i].length());
  }
  
  const size_t width = max_len + 2;
  for (size_t i=0; i < order.size(); i++) {
    ostringstream name;
    name << order[i] << ":";
    out << left << setw(width) << name.str() << std::fixed << setprecision(12) << (get(order[i]) / 1e9) << endl;
  }
  
  if (print_total) out << left << setw(width) << total << ((now - t_start) / 1e9) << endl;
}


