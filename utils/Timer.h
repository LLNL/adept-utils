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

///
/// @file Timer.h
/// @author Todd Gamblin tgamblin@llnl.gov
/// @author David Beckingsale beckingsale@llnl.gov
///
#ifndef ADEPT_UTILS_TIMER_H_
#define ADEPT_UTILS_TIMER_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include <hires-timers.h>

///
/// Class for timing labeled regions of code.
///
class Timer {
  typedef std::map<std::string, timing_t> timing_map;

  timing_map timings;              /// Map from user-supplied keys to elements
  std::vector<std::string> order;  /// Keys into element map, in insertion order
  timing_t t_start;                  /// Time this Timer was last constructedor cleared.
  timing_t t_last;                   /// Last time restart() or record() was called.
  
  /// Convenience method for getting elts out of const map.
  timing_t get(const std::string& name) const {
    timing_map::const_iterator i = timings.find(name);
    return (i != timings.end()) ? i->second : 0;
  }

  
public:
  Timer();
  Timer(const Timer& other);
  ~Timer();

  /// Empties out all recorded timings so far AND sets last_time to now.
  void clear();

  /// Skips ahead and sets last time to now.
  void fast_forward();

  /// Records time since start or last call to record.
  void record(const std::string& name);

  /// Set last to current time, ready to time named event.
  void start(const std::string& name);

  /// Records time since last start.
  void stop(const std::string& name);

  /// Appends timings from another timer to those for this one.  Also updates
  /// last according to that of other timer.
  Timer& operator+=(const Timer& other);

  /// Returns when the timer was initially constructed
  timing_t start_time() const { return t_start; }

  /// Prints all timings (nicely formatted, in sec) to a file.
  void write(std::ostream& out = std::cout, bool print_total = false) const;

  /// Writes AND clears.
  void dump(std::ostream& out = std::cout, bool print_total = false) {
    write(out, print_total);
    clear();
  }
  
  /// Returns the i-th timing recorded (starting with 0)
  timing_t operator[](const std::string& name) const { 
    return get(name); 
  }

  Timer& operator=(const Timer& other);
};

/// Syntactic sugar; calls write on the timer and passes the ostream.
inline std::ostream& operator<<(std::ostream& out, const Timer& timer) {
  timer.write(out);
  return out;
}


#endif // ADEPT_UTILS_TIMER_H_
