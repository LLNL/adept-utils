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


