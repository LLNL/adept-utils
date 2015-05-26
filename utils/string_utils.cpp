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


#include "string_utils.h"
#include <iostream>
#include <sstream>
using namespace std;

namespace stringutils {
  void split(const string& str, const string& delim, vector<string>& parts) {
    size_t start, end = 0;
    
    while (end < str.size()) {
      start = end;
      while (start < str.size() && (delim.find(str[start]) != string::npos))
        start++;  // skip initial whitespace
      
      end = start;
      while (end < str.size() && (delim.find(str[end]) == string::npos))
        end++; // skip to end of word
      
      if (end-start != 0) {  // just ignore zero-length strings.
        parts.push_back(string(str, start, end-start));
      }
    }
  }

  void split_str(const string& str, const string& delim, vector<string>& parts) {
    size_t start = 0;
    size_t end = 0;
    
    while (start < str.size()) {
      end = str.find(delim, start);
      if (end == string::npos) end = str.size();

      if (end-start != 0) {  // just ignore zero-length strings.
        parts.push_back(string(str, start, end-start));
      }
      
      start = end + delim.size();
    }
  }

  string trim(const string& str, const string chars) {
    size_t start = 0;
    size_t end = str.size();
    
    while (start < str.size() && chars.find(str[start]) != string::npos) 
      start++;
    
    while (end > 0 && chars.find(str[end-1]) != string::npos) {
      end--;
    }
    
    return string(str, start, end - start);
  }

  string times(const string& str, size_t n) {
    ostringstream s;
    for (size_t i=0; i < n; i++) {
      s << str;
    }
    return s.str();
  }

}  // namespace

