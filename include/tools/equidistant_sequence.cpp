//
// Copyright (c) 2017 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "gtest/gtest.h"

#include "equidistant_sequence.h"

TEST(create_equidistant_sequence, basic_forward)
{
   std::string text("Upward, not Northward");
   
   std::function<bool(const char& c)> allchars =
      [] (const char&) { return true; };
   
   struct t_cases {
      std::string::iterator begin;
      std::string::iterator end;
      uint desired_sequence_length;
      uint letters_to_skip_in_between;
      std::function<bool(const char&)> counts_as_letter;
      std::string expected_result;
   } test_cases_forward[] = {
      // basic case
      {text.begin(),   text.end(), 5, 1, isalnum, "Uwrnt"},
      // shift start of the original sequence
      {text.begin()+1, text.end(), 5, 1, isalnum, "padoN"},
      {text.begin()+2, text.end(), 5, 1, isalnum, "wrnto"},
      {text.begin()+3, text.end(), 5, 1, isalnum, "adoNr"},
      // change desired result length
      {text.begin(),   text.end(), 6, 1, isalnum, "Uwrnto"},
      {text.begin(),   text.end(), 7, 1, isalnum, "Uwrntot"},
      {text.begin(),   text.end(), 8, 1, isalnum, "Uwrntotw"},
      // change number of letters to skip in between
      {text.begin(),   text.end(), 5, 2, isalnum, "UanNt"},
      {text.begin(),   text.end(), 5, 3, isalnum, "Urttr"},
      {text.begin(),   text.end(), 4, 4, isalnum, "Udoa"},
      // when all chars matter
      {text.begin(),   text.end(), 5, 1, allchars, "Uwr,n"}, // basic
      {text.begin()+1, text.end(), 5, 1, allchars, "pad o"}, // shift start
      {text.begin(),   text.end(), 6, 1, allchars, "Uwr,nt"}, // length
      {text.begin(),   text.end(), 5, 2, allchars, "Ua,oN"}, // # skips
   };
   
   for(const auto& test_case : test_cases_forward)
   {
      auto eds = mzlib::create_equidistant_sequence<std::string>(
      test_case.begin,
      test_case.end,
      test_case.desired_sequence_length,
      test_case.letters_to_skip_in_between,
      test_case.counts_as_letter);
      ASSERT_TRUE(eds.has_value());
      ASSERT_EQ(test_case.expected_result, eds.value());
   }
}

TEST(create_equidistant_sequence, basic_backward)
{
   std::string text("Upward, not Northward");

   std::function<bool(const char& c)> allchars =
      [] (const char&) { return true; };
   
   struct t_cases {
      std::string::reverse_iterator begin;
      std::string::reverse_iterator end;
      uint desired_sequence_length;
      uint letters_to_skip_in_between;
      std::function<bool(const char&)> counts_as_letter;
      std::string expected_result;
   } test_cases_backward[] = {
      // basic case
      {text.rbegin(),   text.rend(), 5, 1, isalnum, "dahrN"},
      // shift start of the original sequence
      {text.rbegin()+1, text.rend(), 5, 1, isalnum, "rwtot"},
      {text.rbegin()+2, text.rend(), 5, 1, isalnum, "ahrNo"},
      {text.rbegin()+3, text.rend(), 5, 1, isalnum, "wtotn"},
      // change desired result length
      {text.rbegin(),   text.rend(), 6, 1, isalnum, "dahrNo"},
      {text.rbegin(),   text.rend(), 7, 1, isalnum, "dahrNod"},
      {text.rbegin(),   text.rend(), 8, 1, isalnum, "dahrNoda"},
      // change number of letters to skip in between
      {text.rbegin(),   text.rend(), 5, 2, isalnum, "dwrtd"},
      {text.rbegin(),   text.rend(), 5, 3, isalnum, "dhNdp"},
      {text.rbegin(),   text.rend(), 4, 4, isalnum, "dtow"},
      // when all chars matter
      {text.rbegin(),   text.rend(), 6, 1, allchars, "dahrNt"}, // basic
      {text.rbegin()+1, text.rend(), 5, 1, allchars, "rwto "}, // shift start
      {text.rbegin(),   text.rend(), 7, 1, allchars, "dahrNtn"}, // length
      {text.rbegin(),   text.rend(), 5, 2, allchars, "dwr n"}, // # skips
   };
   
   for(const auto& test_case : test_cases_backward)
   {
      auto eds = mzlib::create_equidistant_sequence<std::string>(
      test_case.begin,
      test_case.end,
      test_case.desired_sequence_length,
      test_case.letters_to_skip_in_between,
      test_case.counts_as_letter);
      ASSERT_TRUE(eds.has_value());
      ASSERT_EQ(test_case.expected_result, eds.value());
   }
}

TEST(create_equidistant_sequence, beginning_with_punctuation)
{
   std::string text("..Upward, not Northward");
   
   auto eds = mzlib::create_equidistant_sequence<std::string, char>(
      text.begin(),
      text.end(),
      5, // desired sequence length
      1, // letters to skip in between,
      isalnum);
      
   ASSERT_TRUE(eds.has_value());
   ASSERT_EQ("Uwrnt", eds.value());
}

TEST(create_equidistant_sequence, not_enough_letters)
{
   std::string text("Upward, not Northward");
   
   auto eds = mzlib::create_equidistant_sequence<std::string, char>(
      text.begin(),
      text.end(),
      5, // desired sequence length
      5, // letters to skip in between,
      isalnum);
      
   ASSERT_FALSE(eds.has_value());
}

TEST(create_equidistant_sequence, just_enough_letters)
{
   std::string text("Upward, not Northwardd");
   //                .  .    .   .  .  .  . 
   
   auto eds = mzlib::create_equidistant_sequence<std::string, char>(
      text.begin(),
      text.end(),
      7, // desired sequence length
      2, // letters to skip in between,
      isalnum);
      
   ASSERT_TRUE(eds.has_value());
   ASSERT_EQ("UanNtad", eds.value());
}

TEST(create_equidistant_sequence, another_type_of_container)
{
   std::vector<int> v = {1,2,3,4,5,0,0,6,7,8,0,9,10,11,12,13,14,15};

   std::function<bool(const int& i)> counts_as_letter =
      [] (const int& i) -> bool
      { // what counts as valid letter
         if (i==0) return false; 
         else return true; 
      };
   
   auto eds = mzlib::create_equidistant_sequence<std::vector<int>>(
      v.begin()+2,
      v.end(),
      5, // desired sequence length
      2, // letters to skip in between,
      counts_as_letter);
      
   ASSERT_TRUE(eds.has_value());
   ASSERT_EQ(std::vector<int>({3,6,9,12,15}), eds.value());
}