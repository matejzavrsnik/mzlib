//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SENTENCE_O_MATIC_H
#define MZLIB_SENTENCE_O_MATIC_H

#include <set>

#include "../greatest_hits/markov_chain.h"
#include "../string/sentence_assemblarator.h"
#include "../string/split_on_punctuation.h"
#include "../string/remove_substrings.h"

namespace mzlib {

class sentence_o_matic_builder : public markov_chain_builder<std::string>
{
public:
   
   virtual void add_state (std::string next_state) override
   {
      std::vector<std::string> split = split_on_puctuation(next_state);
      for (auto& word : split) {
         markov_chain_builder<std::string>::add_state(word);
      }
   }
   
};
   
// specialisation of generic markov chain generator that generates sentences
class sentence_o_matic : public markov_chain_traverser<std::string>
{
   
public:
   
   using markov_chain_traverser::markov_chain_traverser;
        
   virtual const std::string get_next () override
   {
      set_random_next_state();
      std::string sentence = sentence_assemblarator(
         [&]() {
            return markov_chain_traverser<std::string>::get_next();
         });
      // by preventing some words we enabled weird combinations like the
      // following, that are better if they are removed:
      sentence = remove_all_occurences_of_substring(sentence, " ()");
      sentence = remove_all_occurences_of_substring(sentence, " \"\"");
      return sentence;
   }
        
};

} // namespace
    
#endif /* MZLIB_SENTENCE_O_MATIC_H */
