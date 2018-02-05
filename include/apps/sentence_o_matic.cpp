//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "sentence_o_matic.h"

TEST(sentence_o_matic, demo_test) 
{

   mzlib::sentence_o_matic_builder builder;
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
   
   mzlib::sentence_o_matic sentence_o_matic(builder.wrap_up());
    
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
