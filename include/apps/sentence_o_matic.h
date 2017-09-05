//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#ifndef MZLIB_SENTENCE_O_MATIC_H
#define MZLIB_SENTENCE_O_MATIC_H

#include "../abstract/markov_chain.h"
#include "../string/sentence_assemblarator.h"
#include "../string/split_string_puctuation.h"

namespace mzlib {

// specialisation of generic markov chain generator that generates sentences
class sentence_o_matic : public markov_chain<std::string>
{
        
public:
        
   void read_next (std::string state) override 
   {
      std::vector<std::string> split = split_string_puctuation(state);
      for (auto& word : split) {
         read(word);
      }
   }
        
   std::string get_next () override 
   {
      std::string sentence = sentence_assemblarator([&](){return get();});
      return sentence;
   }
        
};

} // namespace
    
#endif /* MZLIB_SENTENCE_O_MATIC_H */

#ifdef MZLIB_BUILDING_TESTS

#ifndef MZLIB_SENTENCE_O_MATIC_TESTS_H
#define MZLIB_SENTENCE_O_MATIC_TESTS_H

TEST(sentence_o_matic, demo_test) 
{
   mzlib::sentence_o_matic sentence_o_matic;
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
      sentence_o_matic.read_next(word);
   }
   while(ss);
   sentence_o_matic.wrap_up();
    
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

#endif // MZLIB_BUILDING_TESTS
