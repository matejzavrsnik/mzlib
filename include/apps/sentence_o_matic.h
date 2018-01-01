//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SENTENCE_O_MATIC_H
#define MZLIB_SENTENCE_O_MATIC_H

#include <set>

#include "../abstract/markov_chain.h"
#include "../string/sentence_assemblarator.h"
#include "../string/split_on_puctuation.h"
#include "../string/remove_substrings.h"

namespace mzlib {

class sentence_o_matic_builder : public markov_chain_builder<std::string>
{
public:
   
   using markov_chain_builder::markov_chain_builder;
   
   virtual void add_state (std::string next_state) override
   {
      std::vector<std::string> split = split_on_puctuation(next_state);
      for (auto& word : split) {
         markov_chain_builder<std::string>::add_state(word);
      }
   }
   
};
   
// specialisation of generic markov chain generator that generates sentences
class sentence_o_matic : public markov_chain<std::string>
{
   
public:
        
   virtual const std::string get_next () override
   {
      std::string sentence = sentence_assemblarator(
         [&]() {
            return markov_chain<std::string>::get_next();
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

#ifdef MZLIB_SENTENCE_O_MATIC_TESTS_H
#undef MZLIB_SENTENCE_O_MATIC_TESTS_H

TEST(sentence_o_matic, demo_test) 
{
   mzlib::sentence_o_matic sentence_o_matic;
   mzlib::sentence_o_matic_builder builder(sentence_o_matic);
   std::stringstream ss(
      "I have always believed, and I still believe, that whatever good or bad fortune may "
      "come our way we can always give it meaning and transform it into something of value. " 
      "What could I say to you that would be of value, except that perhaps you seek too much, " 
      "that as a result of your seeking you cannot find. We are not going in circles, we are "
      "going upwards. The path is a spiral; we have already climbed many steps. It may be important "
      "to great thinkers to examine the world, to explain and despise it. But I think it is only "
      "important to love the world, not to despise it, not for us to hate each other, but to be "
      "able to regard the world and ourselves and all beings with love, admiration and respect."
   );
   std::string word;
   do {
      ss >> word;
      builder.add_state(word);
   }
   while(ss);
   builder.wrap_up();
    
   std::string generated = "";
   do {
      generated += "\n";
      generated += sentence_o_matic.get_next();
   }
   while(generated.length() < 10000);
    
   // uncomment and put a breakpoint on assert to see it work
   // std::cout << generated;
   ASSERT_TRUE(generated.length() >= 10000); // how do you test meaningless content?
}

#endif // MZLIB_SENTENCE_O_MATIC_TESTS_H

