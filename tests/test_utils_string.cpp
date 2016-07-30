//
// Copyright (c) 2015 Matej Zavrsnik
//
// Web:  matejzavrsnik.com
// Mail: matejzavrsnik@gmail.com
//

#include "../include/utils_string.h"
#include "gtest/gtest.h"
    
class fixture_utils_string : public ::testing::Test 
{

protected:

   fixture_utils_string() {}
   virtual ~fixture_utils_string() {}
   virtual void SetUp() {}
   virtual void TearDown() {}
   
};

TEST_F(fixture_utils_string, split_string_puctuation_basic) 
{
   std::string test = ",word!)";
   std::vector<std::string> result = mzlib::util::split_string_puctuation(test);
   ASSERT_EQ(result.size(), 4);
   ASSERT_EQ(result[0], ",");
   ASSERT_EQ(result[1], "word");
   ASSERT_EQ(result[2], "!");
   ASSERT_EQ(result[3], ")");
}

TEST_F(fixture_utils_string, split_string_puctuation_no_punctuations) 
{
   std::string test = "word";
   std::vector<std::string> result = mzlib::util::split_string_puctuation(test);
   ASSERT_EQ(result.size(), 1);
   ASSERT_EQ(result[0], "word");
}

TEST_F(fixture_utils_string, split_string_puctuation_no_punctuations_at_beginning) 
{
   std::string test = "word).";
   std::vector<std::string> result = mzlib::util::split_string_puctuation(test);
   ASSERT_EQ(result.size(), 3);
   ASSERT_EQ(result[0], "word");
   ASSERT_EQ(result[1], ")");
   ASSERT_EQ(result[2], ".");
}

TEST_F(fixture_utils_string, split_string_puctuation_no_punctuations_at_end) 
{
   std::string test = "\",word";
   std::vector<std::string> result = mzlib::util::split_string_puctuation(test);
   ASSERT_EQ(result.size(), 3);
   ASSERT_EQ(result[0], "\"");
   ASSERT_EQ(result[1], ",");
   ASSERT_EQ(result[2], "word");
}

TEST_F(fixture_utils_string, split_string_puctuation_all_punctuations) 
{
   std::string test = "!?.,;:-\"()\n";
   std::vector<std::string> result = mzlib::util::split_string_puctuation(test);
   ASSERT_EQ(result.size(), 11);
   ASSERT_EQ(result[0], "!");
   ASSERT_EQ(result[1], "?");
   ASSERT_EQ(result[2], ".");
   ASSERT_EQ(result[3], ",");
   ASSERT_EQ(result[4], ";");
   ASSERT_EQ(result[5], ":");
   ASSERT_EQ(result[6], "-");
   ASSERT_EQ(result[7], "\"");
   ASSERT_EQ(result[8], "(");
   ASSERT_EQ(result[9], ")");
   ASSERT_EQ(result[10], "\n");
}

TEST_F(fixture_utils_string, wagner_fischer_distance_basic) 
{
   std::string str1 = "matej";
   std::string str2 = "mtey";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 omitted a, 1 substituted y : edit distance = 2
   ASSERT_EQ(2, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_equal) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // it's the same
   ASSERT_EQ(0, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_a_complicated_one) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "mate zavrsnick lykes startrek but and very much the original series because it is too naive.";
   //                     d        a   s        d        sss ssaa   -> 11 changes
   // d: deletion, a: addition, s: substitution
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // a bunch of edits
   ASSERT_EQ(11, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_substition_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "natej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_substition_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive!";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_substition_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much theAoriginal series because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 substitution
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_deletion_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 =  "atej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_deletion_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_deletion_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original eries because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 deletion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_insertion_first) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "Qmatej zavrsnik likes star trek but not so much the original series because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_insertion_last) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.Q";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, wagner_fischer_distance_insertion_middle) 
{
   std::string str1 = "matej zavrsnik likes star trek but not so much the original series because it is too naive.";
   std::string str2 = "matej zavrsnik likes star trek but not so much the original Qseries because it is too naive.";
   
   int result = mzlib::util::wagner_fischer_distance(str1, str2);
   
   // 1 insertion
   ASSERT_EQ(1, result);
}

TEST_F(fixture_utils_string, string_ends_with)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::util::string_ends_with(test_string, "obliteration."));
   ASSERT_FALSE(mzlib::util::string_ends_with(test_string, "bliss."));
}

TEST_F(fixture_utils_string, string_starts_with)
{
   std::string test_string = "Fear is the little-death that brings total obliteration.";
   ASSERT_TRUE (mzlib::util::string_starts_with(test_string, "Fear"));
   ASSERT_FALSE(mzlib::util::string_starts_with(test_string, "Courage"));
}

TEST_F(fixture_utils_string, remove_strings_that_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   auto filtered = mzlib::util::remove_strings_that_end_with (list, {"mind-killer", "obliteration", "me"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));   
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
}


TEST_F(fixture_utils_string, remove_strings_that_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   auto filtered = mzlib::util::remove_strings_that_start_with (list, {"I must", "Fear"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will face my fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I will permit it to pass over me and through me"));
}

TEST_F(fixture_utils_string, remove_strings_that_dont_start_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   auto filtered = mzlib::util::remove_strings_that_dont_start_with (list, {"I must", "Fear"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(3, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "I must not fear"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer")); 
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}

TEST_F(fixture_utils_string, remove_strings_that_dont_end_with)
{
   std::vector<std::string> list;
   list.push_back("I must not fear"); 
   list.push_back("Fear is the mind-killer");
   list.push_back("Fear is the little-death that brings total obliteration");
   list.push_back("I will face my fear");
   list.push_back("I will permit it to pass over me and through me");
   
   auto filtered = mzlib::util::remove_strings_that_dont_end_with (list, {"mind-killer", "obliteration"});
   
   auto not_found = filtered.end();
   ASSERT_EQ(2, filtered.size());
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the mind-killer"));
   ASSERT_NE(not_found, std::find(filtered.begin(), filtered.end(), "Fear is the little-death that brings total obliteration"));
}
