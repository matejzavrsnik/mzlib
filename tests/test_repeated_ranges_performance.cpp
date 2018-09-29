//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/iterators/repeated_ranges.h"

#include "../include/apps/sentence_o_matic.h"
#include "../include/lang/stopwatch.h"

#include <thread>
#include <numeric>
#include <algorithm>

#include "gtest/gtest.h"

namespace
{
   std::string generate_text(int length)
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
      while(generated.length() < length);
    
      return generated;
   }
   
   double run_and_measure(const std::string& text)
   {
      mzlib::stopwatch stopwatch;
      auto start = stopwatch.start();
      
      auto repeats = mzlib::repeated_sequences(
         text.begin(), text.end());
      
      auto end = stopwatch.stop();
      return stopwatch.get_wall_clock(start, end);
   }
}

TEST(repeated_ranges_performance, DISABLED_perform)
{
   std::cout << "l\tt\t" << std::endl;
   
   for (int text_length : {100, 200, 400, 800, 1600, 3200, 6400})
   {
      std::string text = generate_text(text_length);
      
      std::vector<double> times;
      for (int reps=0; reps<1; ++reps)
      {
         times.push_back( run_and_measure(text) );
      }

      double max_time_to_complete = *std::max_element(
         times.begin(), times.end());
      
      // neatly aligned output
      std::cout << std::fixed << std::setprecision(0)
         << text_length << "\t" 
         << max_time_to_complete << "\t"
         << std::endl;
   }
   
   // original
   //l       t
   //100     6
   //200     34
   //400     42
   //800     243
   //1600    1527

   // first round of improvements
   //l       t
   //100     1
   //200     15
   //400     24
   //800     328
   //1600    1256
   
   // implementation with horspool searcher
   //100     6
   //200     25
   //400     44
   //800     229
   //1600    379
   //3200    2755
   //6400    15244



   
   ASSERT_TRUE(true);
}

