//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "symbol_sequences_in_pattern.h"

TEST(first_symbol_sequence_in_pattern, produces_correct_sequence)
{
   std::vector<int> number = {4,5,6,7};
   std::vector<char> sequence = mzlib::first_symbol_sequence_in_pattern(number, mzlib::phone_dial());
   std::string str_sequence(sequence.begin(), sequence.end());
   ASSERT_EQ("gjmp", str_sequence);
}

TEST(next_symbol_sequence_in_pattern, produces_correct_number_of_sequences)
{
   std::vector<int> number = {4,5,6,7};
   std::vector<char> sequence = mzlib::first_symbol_sequence_in_pattern(number, mzlib::phone_dial());
   std::set<std::vector<char>> collection;
   mzlib::option::changed there_was_more;
   do 
   {
      collection.insert(sequence);
      there_was_more = mzlib::next_symbol_sequence_in_pattern(sequence, number, mzlib::phone_dial());
   }
   while (there_was_more == mzlib::option::changed::yes);

   ASSERT_EQ(108, collection.size());
}

TEST(next_symbol_sequence_in_pattern, correctly_increments_sequences)
{
   std::vector<int> number = {4,5,6,7};
   std::vector<char> sequence = mzlib::first_symbol_sequence_in_pattern(number, mzlib::phone_dial());
   std::vector<std::string> collection;
   mzlib::option::changed there_was_more;
   do 
   {
      collection.emplace_back(sequence.begin(), sequence.end());
      there_was_more = mzlib::next_symbol_sequence_in_pattern(sequence, number, mzlib::phone_dial());
   }
   while (there_was_more == mzlib::option::changed::yes);
   
   // start
   ASSERT_EQ("gjmp", collection[0]);
   ASSERT_EQ("hjmp", collection[1]);
   ASSERT_EQ("ijmp", collection[2]);
   ASSERT_EQ("gkmp", collection[3]);
   ASSERT_EQ("hkmp", collection[4]);
   ASSERT_EQ("ikmp", collection[5]);
   ASSERT_EQ("glmp", collection[6]);
   ASSERT_EQ("hlmp", collection[7]);
   
   // somewhere in the middle
   ASSERT_EQ("hkoq", collection[49]);
   ASSERT_EQ("ikoq", collection[50]);
   
   // end
   ASSERT_EQ("hlos", collection[106]);
   ASSERT_EQ("ilos", collection[107]);
}