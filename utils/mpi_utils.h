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


#ifndef MPI_UTILS_H
#define MPI_UTILS_H
///
/// @file mpi_utils.h
/// @brief Overloaded utility functions to convert between arbitrary C/C++ 
///        types and MPI types, custom typedefs for cstdlib types like size_t,
///        and a wrapper for MPI_Pack_Size
///

#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <mpi.h>

//
// Overloaded functions for getting corresponding MPI types for C types.
//
inline MPI_Datatype mpi_typeof(char)                       {return MPI_CHAR;}
inline MPI_Datatype mpi_typeof(signed short)               {return MPI_SHORT;}
inline MPI_Datatype mpi_typeof(signed int)                 {return MPI_INT;}
inline MPI_Datatype mpi_typeof(signed long)                {return MPI_LONG;}
inline MPI_Datatype mpi_typeof(unsigned char)              {return MPI_UNSIGNED_CHAR;}
inline MPI_Datatype mpi_typeof(unsigned short)             {return MPI_UNSIGNED_SHORT;}
inline MPI_Datatype mpi_typeof(unsigned)                   {return MPI_UNSIGNED;}
inline MPI_Datatype mpi_typeof(unsigned long)              {return MPI_UNSIGNED_LONG;}
inline MPI_Datatype mpi_typeof(signed long long)           {return MPI_LONG_LONG_INT;}
inline MPI_Datatype mpi_typeof(double)                     {return MPI_DOUBLE;}
inline MPI_Datatype mpi_typeof(long double)                {return MPI_LONG_DOUBLE;}
inline MPI_Datatype mpi_typeof(std::pair<int,int>)         {return MPI_2INT;}
inline MPI_Datatype mpi_typeof(std::pair<float,int>)       {return MPI_FLOAT_INT;}
inline MPI_Datatype mpi_typeof(std::pair<double,int>)      {return MPI_DOUBLE_INT;}
inline MPI_Datatype mpi_typeof(std::pair<long double,int>) {return MPI_LONG_DOUBLE_INT;}
inline MPI_Datatype mpi_typeof(std::pair<short,int>)       {return MPI_SHORT_INT;}

// 
// Handy datatypes for stdlib datatypes
// @todo these won't work in heterogeneous environments, as it's tied to the machine type.
// 
#define MPI_SIZE_T      (mpi_typeof(size_t()))
#define MPI_INTPTR_T    (mpi_typeof(intptr_t()))
#define MPI_UINTPTR_T   (mpi_typeof(uintptr_t()))

///
/// Expression-ifies the overly C-ish MPI_Pack_size function.  Just returns 
/// the size instead of requring a temporary.
///
inline int mpi_packed_size(int count, MPI_Datatype type, MPI_Comm comm) {
  int size;
  MPI_Pack_size(count, type, comm, &size);
  return size;
}

///
/// PMPI binding for mpi_packed_size().
///
inline int pmpi_packed_size(int count, MPI_Datatype type, MPI_Comm comm) {
  int size;
  PMPI_Pack_size(count, type, comm, &size);
  return size;
}


#endif // MPI_UTILS_H
