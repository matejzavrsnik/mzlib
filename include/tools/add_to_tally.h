//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_ADD_TO_TALLY_H
#define MZLIB_ADD_TO_TALLY_H

#include <map>

namespace mzlib {
    
// Useful for when you use map to count occurrences
template <class Key, class Value>
void add_to_tally(std::map<Key, Value>& word_map, const Key& word)
{
   word_map[word] = (word_map.count(word) == 0 ? 1 : word_map[word] += 1);
}

} // namespace

#endif // MZLIB_ADD_TO_TALLY_H
