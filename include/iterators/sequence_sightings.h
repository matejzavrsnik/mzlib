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
   
template<typename It> 
struct sequence_sightings 
{
   using distance_type = 
      typename std::iterator_traits<It>::difference_type;
   
   std::vector<It> locations;
   distance_type length; 
};

} // namespace

#endif // MZLIB_SEQUENCE_SIGHTING_H
