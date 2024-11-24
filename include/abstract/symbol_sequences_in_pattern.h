//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SYMBOL_SEQUENCES_IN_PATTERN_H
#define SYMBOL_SEQUENCES_IN_PATTERN_H

#include "../iterators/is_last.h"
#include "../lang/binary_options.h"
#include <map>
#include <algorithm>

namespace mzlib {

inline const std::map<int, std::vector<char>>& phone_dial()
{
   static std::map<int, std::vector<char>> dial {
      {0, {'+'}}, // 0
      {1, {'#'}}, // 1
      {2, {'a','b','c'}}, // 2
      {3, {'d','e','f'}}, // 3
      {4, {'g','h','i'}}, // 4
      {5, {'j','k','l'}}, // 5
      {6, {'m','n','o'}}, // 6
      {7, {'p','q','r','s'}}, // 7
      {8, {'t','u','v'}}, // 8
      {9, {'w','x','y','z'}} // 9
   };
   
   return dial;
}

template<class Value, class Symbol>
std::vector<Symbol> first_symbol_sequence_in_pattern(
   std::vector<Value> pattern,
   const std::map<Value, std::vector<Symbol>>& symbols)
{
    std::vector<Symbol> result;
    for (auto value : pattern) 
    {
        Symbol symbol = *(symbols.at(value).begin());
        result.push_back(symbol);
    }
    return result;
}

// Creates sequences of symbols where you can define which symbols can
// appear in place of values in value pattern. For example, if 0 can represent
// a and b, and 1 can represent c and d, this will generate sequences of letters
// for given number pattern. Of course, instead of numbers it can be anything
// and instead of letters it can be anything.
template<class Value, class Symbol>
option::changed next_symbol_sequence_in_pattern(
   std::vector<Symbol>& symbol_sequence,
   const std::vector<Value>& value_pattern, 
   const std::map<Value, std::vector<Symbol>>& symbols_for_value)
{
   for (size_t i=0; i<value_pattern.size(); ++i) 
   {
      // find a symbol for this particular value in pattern
      auto symbol_it = std::find(
         symbols_for_value.at(value_pattern[i]).begin(), 
         symbols_for_value.at(value_pattern[i]).end(), 
         symbol_sequence[i]);
      
      // if this is the last possible symbol for this value, try with value in the next position
      if (is_last(symbol_it, symbols_for_value.at(value_pattern[i]))) 
         continue;

      // assing next symbol for this value to this position in pattern
      symbol_sequence[i] = *(++symbol_it);
      
      // as soon as this position in symbol sequence is changed, reset all previous
      // positions to first possible symbol. Imagine this as counting, but in reverse.
      // Let's assume trinary numeral system for simplicity (read from left to right):
      //    000  -> 100 -> 200 -> 010* -> 110 -> 210 -> 020* -> 120 -> 220 ->  
      // -> 001* -> 101 -> 201 -> 011* -> 111 -> 211 -> 021* -> 121 -> 221 ->
      // -> 002* -> 102 -> 202 -> 012* -> 112 -> 212 -> 022* -> 122 -> 222
      // Notice how in every case when a number increases, all previous numbers are reset to 0.
      // Occurances are marked with * for easier spotting.
      for(;i>0;--i) 
         symbol_sequence[i-1] = *symbols_for_value.at(value_pattern[i-1]).begin();

      // if one position in sequence is increased then we're done, bail out, report progress.
      return option::changed::yes;
   }
   return option::changed::no;
}

} // namespace

#endif /* SYMBOL_SEQUENCES_IN_PATTERN_H */
