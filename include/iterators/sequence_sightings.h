//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SEQUENCE_SIGHTING_H
#define MZLIB_SEQUENCE_SIGHTING_H

#include <iterator>

namespace mzlib {

// To mark in which locations can we find a particular sequence.
   
template<typename It, typename SizeT = long unsigned> 
struct sequence_sightings 
{
   std::vector<It> locations;
   SizeT length; 
};

} // namespace

#endif // MZLIB_SEQUENCE_SIGHTING_H
