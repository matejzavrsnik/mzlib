//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_INDEX_ITERATOR_CONVERSIONS_H
#define MZLIB_INDEX_ITERATOR_CONVERSIONS_H

namespace mzlib {
    
// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from coordinates to array index
inline uint get_index_from_coordinates(
   const std::array<uint,2>& coordinates, 
   uint const row_size)
{
   return (coordinates[0] + row_size*coordinates[1]);
}

// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from array index to coordinates
inline std::array<uint,2> get_coordinates_from_index(
   uint const index, 
   uint const row_size)
{
   return {
      index % row_size,
      index / row_size
   };
}

} // namespace

#endif // MZLIB_INDEX_ITERATOR_CONVERSIONS_H
