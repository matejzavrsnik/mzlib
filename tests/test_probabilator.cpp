//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/probabilator.h"
#include "gtest/gtest.h"

class fixture_probabilator : public ::testing::Test 
{

protected:
   
   fixture_probabilator () {}
   virtual ~fixture_probabilator () {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_probabilator, demo_test) 
{
   mzlib::cprobabilator<int> probabilator;
   probabilator.add_event(0, 10); // event 1, probability 10%
   probabilator.add_event(1, 30); // event 2, probability 30%
   probabilator.add_event(2, 60); // event 3, probability 60%
   probabilator.wrap_up();
    
   std::vector<int> event_occurences = {0,0,0};
   int repetitions = 10000;
   for(int i=0; i<repetitions; ++i) {
      int event = probabilator.get_event();
      event_occurences[event]++;
   }
    
   ASSERT_NEAR(event_occurences[0], repetitions*0.1, repetitions*0.02); // event 0 happened 1000 times +- 200
   ASSERT_NEAR(event_occurences[1], repetitions*0.3, repetitions*0.02); // event 1 happened 3000 times +- 200
   ASSERT_NEAR(event_occurences[2], repetitions*0.6, repetitions*0.02); // event 2 happened 6000 times +- 200
}
