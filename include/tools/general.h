//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_UTILITIES_H
#define MZLIB_UTILITIES_H

#include <string>
#include <iomanip> // std::setprecision
#include <sstream>
#include <vector>
#include <functional> // std::function
#include <limits> // std::numeric_limits
#include <algorithm> // std::find
#include <map>
#include <cstring>
#include <numeric> // std::accumulate
#include "../lang/binary_options.h"
#include "../nature/vector.h"

namespace mzlib {
        
template<typename T> std::size_t 
get_number_of_decimals (T num)
{
   //todo: needs special rule for denormalised values
   // convert to string first
   std::stringstream ss;
   const int precision = std::numeric_limits<double>::digits10 + 1;
   ss << std::setprecision( precision )
      << std::fixed;
   ss << num;
   std::string str = ss.str();
   // cut out everything but decimal places
   auto pos_of_decimal = str.find_first_of(".,");
   auto pos_of_last_non_zero = str.find_last_of("123456789");
   if (pos_of_decimal == std::string::npos ||
       pos_of_last_non_zero == std::string::npos ||
       pos_of_decimal > pos_of_last_non_zero) 
   {
      return 0;
   }
   else {
      str = str.substr(pos_of_decimal+1, pos_of_last_non_zero-1);
   }
   // count 
   return str.length();
}
    
// adds to vector, unless the element is already in
// returns iterator to element in the vector
template<class T> typename std::vector<T>::iterator 
push_back_unique (std::vector<T>& v, const T& element) 
{
   auto sought_element = std::find(v.begin(), v.end(), element);
   if (sought_element == v.end()) {
      v.push_back(element);
      sought_element = --v.end();
   }
   return sought_element;
}
    
// converts iterator to index
template<class T> typename std::vector<T>::difference_type
get_index (std::vector<T>& v, typename std::vector<T>::iterator& it) 
{
   return std::distance(v.begin(), it);
}

// creates vector of vectors; a matrix, so to speak
template<class T> std::vector<std::vector<T>>
create_matrix (size_t first_dim, size_t second_dim, T initial_value)
{
   std::vector<int> line(second_dim, initial_value);
   std::vector<std::vector<int>> matrix(first_dim, line);
   return std::move(matrix);
}

template<class T> void copy_first_n_over_rest (std::vector<T>& v, size_t n)
{
   if (n >= v.size()) return;
   for (uint to = n, from = 0; to < v.size(); ++to, from = to % n) {
      v[to] = v[from];
   }
}

// given a language token generator, this function assembles sentences.
// Tokens can be punctuation marks or words.
// Stops when words generator produces one of sentence ending punctuations: .?!
inline std::string sentence_assemblarator (std::function<std::string()> words_generator) 
{
   // get first word
   std::string word = words_generator();
   // reset state variables
   bool open_quotes = false;
   bool open_parentheses = false;
   char previous_punctuation = 0;
   // start with uppercase word
   word[0] = toupper(word[0]);
   std::string sentence = word;
   // append other words until .?! char
   while (word[0]!='.' && word[0]!='!' && word[0]!='?') {
      word = words_generator();
      // control states of quotes and parentheses
      if (word[0]=='\"') {
         if (previous_punctuation == '\"') continue; // can't have two quotes in a row
         open_quotes = !open_quotes;
      }
      if (word[0]=='(') {
         if(open_parentheses) continue; // can't have ( and then ( again
         open_parentheses = true;
      }
      if (word[0]==')') {
         if (!open_parentheses) continue; // can't have ) without first having (
         open_parentheses = false;
      }
      // prepend space
      bool prepend_space = true;
      if (ispunct(word[0])) {
         prepend_space = false;
         if (word[0]=='\"' && open_quotes) {
            prepend_space = true;
         }
         else if (word[0]=='(' && open_parentheses) {
            prepend_space = true;
         }
      }
      else { // not punctuation
         if (previous_punctuation=='\"' && open_quotes) {
            prepend_space = false;
         }
         else if (previous_punctuation=='(') {
            prepend_space = false;
         }
      } 
      if (prepend_space) { 
         sentence += " ";
      }
      // close parentheses and quotes
      if (word[0]=='.' || word[0]=='!' || word[0]=='?') {
         if (open_parentheses) {
            sentence += ")"; // close the parentheses before the sentence ends
            open_parentheses = false;
         }
         if (open_quotes) {
            sentence += "\""; // close the quotes before the sentence ends
            open_quotes = false;
         }
      }
      previous_punctuation = word[0]; // remember state of punctuation
      sentence += word;
   }
   return sentence;
}

// Returns the smallest of three numbers 2x-3x faster than std::min({i,j,k})
template <class T> T& fast_min_ref (T& min1, T& min2, T& min3)
{
   // Beware, min-field ahead!
   return 
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3);
}

template <class T> T&& fast_min (T&& min1, T&& min2, T&& min3)
{
   // Beware, min-field ahead!
   return std::move(
      min1 < min2 ?
         (min1 < min3 ? min1 : min3) :
         (min2 < min3 ? min2 : min3));
}

// Parses main function arguments in form of "--name=value"
inline std::map<std::string, std::string> 
parse_arguments (int argc, char **argv)
{
   std::map<std::string, std::string> arguments;
   if (argc>1) // 0 is executable name
   {
      for (int index = 1; index < argc; ++index)
      {
         if(strncmp(argv[index], "--", 2) == 0)
         {
            const char* name_start = argv[index] + 2;
            size_t name_size = strchr(name_start, '=') - name_start;
            const char* value_start = name_start + name_size + 1;
            size_t value_size = strlen(value_start);
            std::string name(name_start, name_size);
            std::string value(value_start, value_size);
            arguments[name] = value;
         }
      }
   }
   return arguments;
}

// Useful for when you use map to count occurrences
template <class Key, class Value>
void add_to_tally(std::map<Key, Value>& word_map, const Key& word)
{
   word_map[word] = (word_map.count(word) == 0 ? 1 : word_map[word] += 1);
}

// Map is already intrinsically sorted by keys, but what if you need items sorted
// by values instead?
template <class Key, class Value>
std::vector<std::pair<Key, Value>> sort_map_by_value(
   const std::map<Key,Value>& unsorted, 
   option::descending descending = option::descending::no)
{
   std::vector<std::pair<Key, Value>> result;
   
   std::copy (unsorted.begin(),unsorted.end(),std::back_inserter(result));
   
   std::sort(result.begin(), result.end(), 
      [&descending](const std::pair<Key, Value>& a, const std::pair<Key, Value>& b) 
      {
         return descending ? 
            b.second < a.second : 
            b.second > a.second;   
      });
   return result;
}

// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from coordinates to array index
inline uint get_index_from_coordinates(vector<uint,2> const coordinates, uint const row_size)
{
   return (coordinates[0] + row_size*coordinates[1]);
}

// useful when representing a matrix with one-dimensional array
// conversion function, that will convert from array index to coordinates
inline vector<uint,2> get_coordinates_from_index(uint const index, uint const row_size)
{
   return {
      index % row_size,
      index / row_size
   };
}

// after last element continue from the first again
template<class Iterator>
void circular_increment(Iterator &iterator, Iterator first, Iterator last)
{
   if(++iterator == last) iterator = first;
}

// calculate average of all container elements
template<class Iterator>
double average(Iterator first, Iterator last)
{
   double sum = std::accumulate(first, last, 0);
   double avg = sum / std::distance(first, last);
   return avg;
}

// recursively calculate factorial
template<class T>
T factorial(T number)
{   
   T result = number;
   while(number > 2)
   {
      --number;
      result *= number;
   }
   return result;
}





} // namespace

#endif /* MZLIB_UTILITIES_H */

