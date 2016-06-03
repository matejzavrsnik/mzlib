//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <iomanip> // std::setprecision
#include <sstream>
#include <vector>
#include <functional> // std::function
#include <limits> // std::numeric_limits
#include <algorithm> // std::find

namespace mzlib {
namespace util {
        
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
      // close paretheses and quotes
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
      previous_punctuation = word[0]; // remember state of punctuaction
      sentence += word;
   }
   return sentence;
}
    
} } // namespace mzlib::util

#endif // UTILITIES_H

