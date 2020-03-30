//
// Copyright (c) 2018 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "repeated_ranges.h"

#include "gtest/gtest.h"

TEST(repeated_ranges, demo) 
{
   std::string text = "We are the Borg. " 
                      "Lower your shields and surrender your ships. "
                      "We will add your biological and technological "
                      "distinctiveness to our own. Your culture will "
                      "adapt to service us. Resistance is futile.";
   
   struct
   {
      std::string repeated_string;
      std::string::iterator repeat[2];
   } 
   expected_repeats[] = {
      {
         "er your shi",
         {  text.begin() + 20,
            text.begin() + 47 }
      },
      {
         "e will ad",
         {  text.begin() + 63,
            text.begin() + 147 }
      },
      {
         "ological ",
         {  text.begin() + 81,
            text.begin() + 99 }
      },
   };
   
   int minimum_range_size = 7;
   auto repeats = mzlib::repeated_sequences(
      text.begin(), text.end(), minimum_range_size);
   
   std::string::iterator from;
   
   // there were three different repetitions
   ASSERT_EQ(3, repeats.size());
   for(int repeat : {0,1,2})
   // each happened in two places
   for(int place : {0,1})
   {
      ASSERT_EQ(2, repeats[repeat].locations.size());
      
      from = repeats[repeat].locations[place];

      ASSERT_EQ(expected_repeats[repeat].repeat[place], from);
      
      std::string reconstructed_string(from, from+repeats[repeat].length);
      ASSERT_EQ(expected_repeats[repeat].repeated_string, reconstructed_string);
   }
}
