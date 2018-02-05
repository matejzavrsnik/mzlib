//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "get_random.h"

TEST(get_random_element, demo) 
{
   std::vector<int> example = {0,1,2,3};
    
   int repetitions = 40000;
   std::vector<int> event_occurences = {0,0,0,0};
   for(int i=0; i<repetitions; ++i) {
      auto selected_it = mzlib::get_random_element(example.begin(), example.end());
      int event = *selected_it;
      event_occurences[event]++;
   }
    
   ASSERT_NEAR(event_occurences[0], repetitions*0.25, repetitions*0.02); // event 0 happened 1000 times +- 200
   ASSERT_NEAR(event_occurences[1], repetitions*0.25, repetitions*0.02); // event 1 happened 1000 times +- 200
   ASSERT_NEAR(event_occurences[2], repetitions*0.25, repetitions*0.02); // event 2 happened 1000 times +- 200
   ASSERT_NEAR(event_occurences[3], repetitions*0.25, repetitions*0.02); // event 2 happened 1000 times +- 200
}

TEST(get_random_element, size_one) 
{
   std::vector<int> example;
   example.push_back(1);
   auto random_element = mzlib::get_random_element(example.begin(), example.end());
   ASSERT_EQ(example.begin(), random_element);
}