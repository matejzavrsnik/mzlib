//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef SENTENCE_O_MATIC_H
#define SENTENCE_O_MATIC_H

#include "markov_chain.h"

namespace mzlib {

// specialisation of generic markov chain generator that generates sentences
class csentence_o_matic : public cmarkov_chain<std::string>
{
        
public:
        
   void read_next (std::string state) override 
   {
      std::vector<std::string> split = util::split_string_puctuation(state);
      for (auto& word : split) {
         read(word);
      }
   }
        
   std::string get_next () override 
   {
      std::string sentence = util::sentence_assemblarator([&](){return get();});
      return sentence;
   }
        
};

} // namespace mzlib
    
#endif // SENTENCE_O_MATIC_H

